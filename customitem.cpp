//------------------------------------------------------------------------------
//      Created : 2015-2-11
//       Author : Dmitry Sokolov <mr.dmitry.sokolov@gmail.com>
//  Description :
//------------------------------------------------------------------------------

#include "customitem.h"

#if defined(FBO__)
#include <QOpenGLFramebufferObjectFormat>
#endif


static bool initialized = false;


#if !defined(FBO__)

CustomItemBase::CustomItemBase(QQuickItem *parent) :
        QQuickItem(parent), m_renderer(nullptr)
{
    connect(this, &CustomItemBase::windowChanged, this, &CustomItemBase::handleWindowChanged);
}

CustomItemBase::~CustomItemBase()
{
    cleanup();
}

void CustomItemBase::handleWindowChanged(QQuickWindow * win)
{
    if (win) {
        // Since this call is executed on the rendering thread it must be a Qt::DirectConnection
        connect(win, &QQuickWindow::beforeSynchronizing, this, &CustomItemBase::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &CustomItemBase::cleanup, Qt::DirectConnection);

        // If we allow QML to do the clearing, they would clear what we paint and nothing would show.
        win->setClearBeforeRendering(false);
    }
}

void CustomItemBase::sync()
{
    if (!m_renderer) {
        m_renderer = new CustomItemRenderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &CustomItemRenderer::render, Qt::DirectConnection);
    }
    qreal itemWidth = width();
    qreal itemHeight = height();
    int w_ = std::floor( (itemWidth < 1e-10 ? implicitWidth() : itemWidth) + 0.5 );
    int h_ = std::floor( (itemHeight < 1e-10 ? implicitHeight() : itemHeight) + 0.5 );
    int x_ = x();
    int y_ = parentItem()->y() + parentItem()->height() - y() - height();
    m_renderer->setViewport(QRectF(x_, y_, w_, h_));
}

void CustomItemBase::cleanup()
{
    if (m_renderer) {
        delete m_renderer;
        m_renderer = nullptr;
        initialized = false;
    }
}

#else

QOpenGLFramebufferObject * CustomItemRenderer::createFramebufferObject(const QSize & size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}

#endif

void CustomItemRenderer::render()
{
#if !defined(FBO__)
    if (!initialized) {
        initializeOpenGLFunctions();
        initialized = true;
    }

    glViewport(m_viewport.left(), m_viewport.top(), m_viewport.width(), m_viewport.height());

    glEnable(GL_SCISSOR_TEST);
    glScissor(m_viewport.left(), m_viewport.top(), m_viewport.width(), m_viewport.height());
#endif

    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

#if !defined(FBO__)
    glDisable(GL_SCISSOR_TEST);
#endif
}
