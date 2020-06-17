#include "Sprite.h"


class AnimatedSprite : public Sprite
{
public:
	virtual void Initialize() override;
protected:
	virtual void PrecacheAnimation(std::string name, std::string path, std::string extension, int length);
	virtual void RenderAnimation(std::string name, float AnimationSpeed);
private:
	typedef Sprite Super;
};
