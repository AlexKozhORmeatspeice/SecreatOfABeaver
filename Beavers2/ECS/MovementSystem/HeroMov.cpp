#include "HeroMov.h"
std::vector<HeroMov*> HeroMov::movComps;

HeroMov::HeroMov()
{
	movComps.push_back(this);
	
	moveCost = 10;
	speed = stamina->GetCellSize();
}
HeroMov::HeroMov(unsigned int nowMoveCost)
{
	movComps.push_back(this);

	moveCost = nowMoveCost;
	speed = stamina->GetCellSize();
}

void HeroMov::init()
{
	isMoving = false;
	isChoosed = false;
	canMove = false;

	pos = entity->GetComponent<PositionComponent>();

	stamina = entity->GetComponent<Stamina>();

	circleMoveEntity = &CreatObj();

	circleMoveEntity->AddComponent<PositionComponent>();
	circlePos = circleMoveEntity->GetComponent<PositionComponent>();
	circlePos->SetPos(pos->GetPos());

	circleMoveEntity->AddComponent<Circle>(1.0f);
	circle = circleMoveEntity->GetComponent<Circle>();
	circle->Unactivate();
}


void HeroMov::update()
{
	if (canMove)
	{
		Move();
	}
	else
	{
		targetPoint = pos->GetPos();
	}

	int mouseLeftState = GLFWGetKeyMouseState(GLFW_MOUSE_BUTTON_LEFT);
	int mouseRightState = GLFWGetKeyMouseState(GLFW_MOUSE_BUTTON_RIGHT);

	//check which hero set active
	for (auto* coll : movComps)
	{
		if (mouseLeftState == GLFW_PRESS && Coursor::GetCollision<BoxCollider>(coll->entity))
		{
			coll->isChoosed = true;
			SetOtherNotChoosed(coll); 
			break;
		}
	}
	if (!isChoosed)
		return;

	bool inMoveRadius = stamina->CanMove(Coursor::GetMousePos(), pos->GetPos(), moveCost);
	bool gotClickNotOnObject = (
								mouseLeftState == GLFW_PRESS && 
								!Coursor::GetCollision<BoxCollider>(entity)
							   );
	
	//if get right mouse or click to move out of move distance set not choosed
	if (mouseRightState == GLFW_PRESS || (gotClickNotOnObject && !inMoveRadius))
	{
		isChoosed = false;
		return;
	}

	//if got right click of left mouse start move
	if (!isMoving && !canMove && gotClickNotOnObject && inMoveRadius)
	{
		isChoosed = false;
		canMove = true;
		SetTarget();

		stamina->UseStaminaToMove(targetPoint, pos->GetPos(), moveCost);
	}
}

void HeroMov::Move()
{
	if (glm::distance(targetPoint, pos->GetPos()) <= stamina->GetCellSize())
	{
		std::cout << 2 << std::endl;
		canMove = false;
		isMoving = false;
		return;
	}
	
	isMoving = true;

	glm::vec3 dir = targetPoint - pos->GetPos();
	dir /= glm::length(dir);

	pos->SetPos(pos->GetPos() + dir * speed);
}

void HeroMov::draw()
{	
	if (isChoosed)
	{
		circle->Activate();
	}
	else
	{
		circle->Unactivate();
		return;
	}
		
	circlePos->SetPos(pos->GetPos());
	circle->SetRadius(stamina->GetMaxDistMove(moveCost) * sqrt(2));

	bool inMoveRadius = stamina->CanMove(Coursor::GetMousePos(), pos->GetPos(), moveCost);

	if (inMoveRadius)
		circle->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	else
		circle->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void HeroMov::SetTarget()
{
	targetPoint = Coursor::GetMousePos();
}

void HeroMov::SetOtherNotChoosed(HeroMov* exceptComp)
{
	for (auto& comp : movComps)
	{
		if (comp == exceptComp)
			continue;

		comp->isChoosed = false;
	}

}

HeroMov::~HeroMov()
{
	delete circleMoveEntity;

	auto it = std::find(movComps.begin(), movComps.end(), this);
	if (it != movComps.end())
		movComps.erase(it);
}