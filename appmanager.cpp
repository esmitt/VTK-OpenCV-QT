#include "appmanager.h"
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkCallbackCommand.h>
#include <vtkWindowToImageFilter.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

//
// Copying the render is displayed in a OpenCV window with
// a blurring effect
// 
/// Class to handle an implementation of an Observer under a Command event
class vtkTimerUser : public vtkCallbackCommand
{
public:
  CQtOpenCVViewerGl* m_pOpenCVViewer;
  // Important! the constructor
  static vtkTimerUser *New()
  {
    return new vtkTimerUser;
  }

  // Function that execute the main code of the Command
  virtual void Execute(vtkObject *caller, unsigned long eventId, void * vtkNotUsed(callData))
  {
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkRenderWindowInteractor::SafeDownCast(caller);
    if (interactor == nullptr) return;

    // Define the filter to extract the image
    vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
    windowToImageFilter->SetInput(interactor->GetRenderWindow());

    // Copy image from VTK to OPENCV
    vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
    imageData = windowToImageFilter->GetOutput();
    windowToImageFilter->Update();

    int windowSize[2];
    interactor->GetSize(windowSize);

    // Pointer array directly
    cv::Mat matImage(windowSize[0], windowSize[1], CV_8UC3, imageData->GetScalarPointer()); // 8 bits x unsigned char x 3 channels
    cv::cvtColor(matImage, matImage, cv::COLOR_BGR2RGB);    // change from BGR --> RGB
    cv::flip(matImage, matImage, cv::ROTATE_90_CLOCKWISE);  // original image is turn down

    m_pOpenCVViewer->showImage(matImage);

    // Safe normally to continue
    interactor->Render();
  }
};

CAppManager::CAppManager(QVTKWidget* pVTKWidget, CQtOpenCVViewerGl* pOpenCVViewer)
{
  // This creates a polygonal cylinder model with eight circumferential facets
  // (i.e, in practice an octagonal prism).
  vtkSmartPointer<vtkCylinderSource> cylinder =
    vtkSmartPointer<vtkCylinderSource>::New();
  cylinder->SetResolution(8);

  // The mapper is responsible for pushing the geometry into the graphics library.
  // It may also do color mapping, if scalars or other attributes are defined.
  vtkSmartPointer<vtkPolyDataMapper> cylinderMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

  // The actor is a grouping mechanism: besides the geometry (mapper), it
  // also has a property, transformation matrix, and/or texture map.
  // Here we set its color and rotate it around the X and Y axes.
  vtkSmartPointer<vtkActor> cylinderActor =
    vtkSmartPointer<vtkActor>::New();
  cylinderActor->SetMapper(cylinderMapper);
  cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
  cylinderActor->RotateX(30.0);
  cylinderActor->RotateY(-45.0);

  // The renderer generates the image
  // which is then displayed on the render window.
  // It can be thought of as a scene to which the actor is added
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(cylinderActor);
  renderer->SetBackground(0.1, 0.2, 0.4);
  // Zoom in a little by accessing the camera and invoking its "Zoom" method.
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.5);

  // The render window is the actual GUI window
  // that appears on the computer screen
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(200, 200);

  // These lines are important:
  // The actual render windows comes from the QVTK widget
  // The Renderer object should be passed to the QVTK widget (actors to be add for example)
  m_pVTKWidget = pVTKWidget;
  renderWindow = m_pVTKWidget->GetRenderWindow();
  m_pVTKWidget->GetRenderWindow()->AddRenderer(renderer);

  m_pVTKWidget->GetInteractor()->CreateRepeatingTimer(500);  //100 milliseconds

  m_pOpenCVViewer = pOpenCVViewer;

  vtkSmartPointer<vtkTimerUser> tCBInstance = vtkSmartPointer<vtkTimerUser>::New();
  tCBInstance->m_pOpenCVViewer = m_pOpenCVViewer;

  m_pVTKWidget->GetInteractor()->AddObserver(vtkCommand::TimerEvent, tCBInstance);
}

CAppManager::~CAppManager()
{
  m_pVTKWidget = nullptr;
  m_pOpenCVViewer = nullptr;
}
