#include "Engine/Level.h"

class SpaceLevel : public Level
{
public:
	void Initialize(RendererBase* r, SoundManager* soundcontroller) override;
	void Render() override;
	void EventHandler(SDL_Event* e) override;
private:
	typedef Level Super;
};
