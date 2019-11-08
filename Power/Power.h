#ifndef POWER_H
#define POWER_H

#define null NULL

constexpr double _g = 9.80665;
constexpr double _m = 16;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <sstream>
#include <string>
#include <iostream>

#include <vector>
#include <unordered_map>

#include "Logging.h"

#include "Queue.h"

#include "Vector2D.h"

#include "Animation.h"
#include "SoundEffect.h"
#include "MusicEffect.h"

#include "Event.h"

#include "ECS.h"

#include "comp_Transform.h"
#include "comp_Sprite.h"
#include "comp_Animator.h"
#include "comp_Rigidbody.h"
#include "comp_Collider.h"
#include "comp_Input.h"
#include "comp_Audio.h"

#include "GameObjectManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "InputManager.h"
#include "MusicManager.h"

#include "Game.h"

#include "Collision.h"
#include "CollisionHandler.h"
#include "InputHandler.h"

#include "Drawable.h"
#include "Line2D.h"

#endif
