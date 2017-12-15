#pragma once

#include <QVTKWidget.h>
#include <cqtopencvviewergl.h>

class CAppManager
{
private:
  std::shared_ptr<QVTKWidget> m_pVTKWidget;
  std::shared_ptr<CQtOpenCVViewerGl> m_pOpenCVViewer;
public:
  CAppManager(QVTKWidget* pVTKWidget, CQtOpenCVViewerGl* pOpenCVViewer);
  ~CAppManager();
};

