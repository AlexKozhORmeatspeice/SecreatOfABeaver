#include "HeroMov.h"

HeroMov::HeroMov()
{
	moveCost = 10;
	speed = stamina->GetCellSize() / 5.0f;
}
HeroMov::HeroMov(unsigned int nowMoveCost)
{
	moveCost = nowMoveCost;
	speed = stamina->GetCellSize() / 5.0f;
}

void HeroMov::init()
{
	heroComp = entity->GetComponent<Hero>();

	isMoving = false;
	canMove = false;

	pos = entity->GetComponent<Transform>();

	stamina = entity->GetComponent<Stamina>();

	Entity& circleMoveEntity = Manager::addEntity();

	circleMoveEntity.AddComponent<Transform>();
	circlePos = circleMoveEntity.GetComponent<Transform>();
	circlePos->SetPos(pos->GetPos());

	circleMoveEntity.AddComponent<Circle>(1.0f);
	circle = circleMoveEntity.GetComponent<Circle>();
	circle->Unactivate();
}


void HeroMov::update()
{
	if (canMove && heroComp->canTakeAction)
	{
		Move();
	}
	
	if (!heroComp->isChoosed)
		return;

	int mouseLeftState = GLFWGetKeyMouseState(GLFW_MOUSE_BUTTON_LEFT);
	bool inMoveRadius = CanMove(Coursor::GetMousePos(), pos->GetPos(), moveCost);
	bool gotClickNotOnObject = (
								mouseLeftState == GLFW_PRESS && 
								!Coursor::GetCollisionStatus<BoxCollider>()
							   );

	//if get right mouse or click to move out of move distance set not choosed
	if (gotClickNotOnObject && !inMoveRadius && !Coursor::isOnUI)
	{
		heroComp->isChoosed = false;
		return;
	}

	//if got left mouse click is right start move
	if (!isMoving && !canMove && gotClickNotOnObject && inMoveRadius && !Coursor::isOnUI)
	{
		SetTarget();
		bool canGoThroughCollision = CanMove(targetPoint, pos->GetPos(), moveCost);

		if (canGoThroughCollision)
		{
			canMove = true;
			heroComp->isChoosed = false;
			UseStaminaToMove(targetPoint, pos->GetPos(), moveCost);
		}
		else
		{
			heroComp->isChoosed = false;
		}
		
	}

}

void HeroMov::Move()
{
	if (glm::distance(targetPoint, pos->GetPos()) <= stamina->GetCellSize() * 2.0f)
	{
		canMove = false;
		isMoving = false;
		return;
	}
	
	isMoving = true;

	glm::vec3 dir = targetPoint - pos->GetPos();
	dir /= glm::length(dir);
	dir.z = 0.0f;

	pos->SetPos(pos->GetPos() + dir * speed);
}

void HeroMov::draw()
{	
	if (heroComp->isChoosed)
	{
		circle->Activate();
	}
	else
	{
		circle->Unactivate();
		return;
	}
		
	circlePos->SetPos(pos->GetPos());
	circle->SetRadius(((float)stamina->GetNowStamina() / (float)moveCost) * (float)stamina->GetCellSize());

	bool inMoveRadius = CanMove(Coursor::GetMousePos(), pos->GetPos(), moveCost);

	if (inMoveRadius)
		circle->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	else
		circle->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void HeroMov::SetTarget()
{
	targetPoint = Raycast::GetPointOfCollision(pos->GetPos(), Coursor::GetMousePos() - pos->GetPos(), entity);

	//targetPoint = Coursor::GetMousePos();
}

bool HeroMov::CanMove(glm::vec3 pos1, glm::vec3 pos2, unsigned int nowMovCost)
{
	unsigned int cellsCount = glm::distance(pos1, pos2) / stamina->GetCellSize();
	unsigned int stamCostMove = cellsCount * nowMovCost;

	return stamCostMove <= stamina->GetNowStamina();
}

void HeroMov::UseStaminaToMove(glm::vec3 pos1, glm::vec3 pos2, unsigned int nowMovCost)
{
	unsigned int cellsCount = glm::distance(pos1, pos2) / stamina->GetCellSize();
	unsigned int stamCostMove = cellsCount * nowMovCost;

	if (!stamina->UseStamina(stamCostMove))
	{
		std::cout << "Not enough stamina" << std::endl;
		canMove = false;
		return;
	}
}

HeroMov::~HeroMov()
{

}