//------------------------------------------------------------------------------
//      Created : 2015-2-11
//       Author : Dmitry Sokolov <mr.dmitry.sokolov@gmail.com>
//  Description :
//------------------------------------------------------------------------------

#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include <QQuickItem>


#define FBO__


#if !defined(FBO__)

#include <QQuickWindow>
#include <QOpenGLFunctions>


class CustomItemRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    void setViewport(const QRectF &vp) { m_viewport = vp; }

public slots:
    virtual void render();

private:
    QRectF  m_viewport;
};


class CustomItemBase : public QQuickItem
{
    Q_OBJECT
public:
    explicit CustomItemBase(QQuickItem * parent = nullptr);
    virtual ~CustomItemBase();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow * win);

protected:
    CustomItemRenderer * m_renderer;
};

#else

#include <QQuickFramebufferObject>


class CustomItemRenderer : public QQuickFramebufferObject::Renderer
{
public:
    CustomItemRenderer() {}
    virtual ~CustomItemRenderer() {}

public:
    virtual void render();
    virtual QOpenGLFramebufferObject * createFramebufferObject(const QSize & size);
};


class CustomItemBase : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    explicit CustomItemBase(QQuickItem *parent = nullptr) : QQuickFramebufferObject(parent) {}

    virtual Renderer * createRenderer() const { return new CustomItemRenderer; }
};

#endif


class CustomItem : public CustomItemBase
{
public:
    CustomItem(QQuickItem * parent = nullptr) : CustomItemBase(parent) {}
    virtual ~CustomItem() {}
};

#endif // CUSTOMITEM_H
