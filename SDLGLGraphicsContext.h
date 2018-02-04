#if !defined(__APPLE__)
#include "SDL_syswm.h"
#endif
#include "SDL.h"

#include "thin3d/GLRenderManager.h"
#include "gfx/gl_common.h"
#include "Common/GraphicsContext.h"

class SDLGLGraphicsContext : public DummyGraphicsContext {
public:
	SDLGLGraphicsContext() {
	}
	~SDLGLGraphicsContext() {
		delete draw_;
	}

	// Returns 0 on success.
	int Init(SDL_Window *&window, int x, int y, int mode, std::string *error_message);

	void Shutdown() override {
#ifdef USING_EGL
		EGL_Close();
#else
		SDL_GL_DeleteContext(glContext);
#endif
	}

	void SwapBuffers() override {
		renderManager_->Swap();
	}

	Draw::DrawContext *GetDrawContext() override {
		return draw_;
	}

	void ThreadStart() override {
		renderManager_->ThreadStart();
	}

	bool ThreadFrame() override {
		return renderManager_->ThreadFrame();
	}

	void ThreadEnd() override {
		renderManager_->ThreadEnd();
	}

private:
	Draw::DrawContext *draw_ = nullptr;
	SDL_Window *window_;
	SDL_GLContext glContext = nullptr;
	GLRenderManager *renderManager_ = nullptr;
};


