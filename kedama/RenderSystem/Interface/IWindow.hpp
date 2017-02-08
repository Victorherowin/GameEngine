#ifndef IWINDOW
#define IWINDOW

#include <string>
#include "../RenderSystemClass.hpp"

namespace Kedama
{
    using std::string;

    class IWindow
    {
    public:
	virtual ~IWindow(){}

	virtual void Create(const string& title,int w,int h)=0;
	virtual void CreateFrom(void* handle){}

	virtual void SetTitle(const string& title)=0;
	virtual void SetSize(int w,int h)=0;
	virtual void SetPosition(int x,int y)=0;
	virtual void SetFullscreen(bool flag)=0;

	virtual const string GetTitle()=0;
	virtual void GetSize(int* w,int* h)=0;
	virtual void GetPosition(int* x,int* y)=0;
    };
}

#endif
