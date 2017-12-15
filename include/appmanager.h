#pragma once

#include <QVTKWidget.h>
#include <cqtopencvviewergl.h>

class CAppManager
{
private:
  QVTKWidget* m_pVTKWidget;
  CQtOpenCVViewerGl* m_pOpenCVViewer;
public:
  CAppManager(QVTKWidget* pVTKWidget, CQtOpenCVViewerGl* pOpenCVViewer);
  ~CAppManager();
};

