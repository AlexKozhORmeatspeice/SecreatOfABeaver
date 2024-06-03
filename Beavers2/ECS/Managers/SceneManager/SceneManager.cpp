#include "SceneManager.h"
void CreateScene1(std::vector<Entity*>&);
void CreateScene2(std::vector<Entity*>&);
void CreateScene3(std::vector<Entity*>&);
void CreateScene4(std::vector<Entity*>&);

int SceneManager::nowScene;	
std::vector<Entity*> SceneManager::currentEntities;
std::vector<void (*)(std::vector<Entity*>&)> SceneManager::scenesFuncs;

void SceneManager::init()
{
	nowScene = 0;

	scenesFuncs.push_back(CreateScene1);
	scenesFuncs.push_back(CreateScene2);
	scenesFuncs.push_back(CreateScene3);
	scenesFuncs.push_back(CreateScene4);
}

void SceneManager::LoadScene(int n)
{
	nowScene = n;
	SaveManager::SaveData();
	ClearScene();
	Manager::refresh();
	scenesFuncs[nowScene](currentEntities); //spawn scenes and give entities
	SaveManager::LoadData();
}


void SceneManager::LoadNextScene()
{
	nowScene++;
	LoadScene(nowScene);
}


void SceneManager::ReloadScene()
{
	ClearScene();
	LoadScene(nowScene);
}

void SceneManager::ClearScene()
{
	for (auto entity : currentEntities)
	{
		entity->destroy();
	}
	currentEntities.clear();
}

////////////////////////////////////////////////////////////////////////////////////scenes////////////////////////////////////////////////////////////////////////////////////
void CreateScene1(std::vector<Entity*>& vec)
{
	CamComponent::SetPos(glm::vec3(0.0f));
	Entity* floor1(&Manager::addEntity());
	Entity* floor2(&Manager::addEntity());
	Entity* stepSys(&Manager::addEntity());
	Entity* wall0(&Manager::addEntity());
	Entity* wall1(&Manager::addEntity());
	Entity* wall2(&Manager::addEntity());
	Entity* wall3(&Manager::addEntity());
	Entity* wall4(&Manager::addEntity());
	Entity* wall5(&Manager::addEntity());
	Entity* message(&Manager::addEntity());

	StepSysManager* stepSM = stepSys->AddComponent<StepSysManager>();

	/////////////////////Heroes and enemies/////////////////////
	Entity* zubar = HeroCreator::ZubarPrefab(glm::vec3(-50.0f, 100.0f, 0.0f));
	stepSM->AddHero(*zubar->GetComponent<Hero>()); //!!!

	Entity* harchok = HeroCreator::HarchokPrefab(glm::vec3(50.0f, 100.0f, 0.0f));
	stepSM->AddHero(*harchok->GetComponent<Hero>()); //!!!


	Entity* motor = HeroCreator::MotorPrefam(glm::vec3(-50.0f, 200.0f, 0.0f));
	stepSM->AddHero(*motor->GetComponent<Hero>()); //!!!

	Entity* nogotochki = HeroCreator::NogotPrefab(glm::vec3(50.0f, 200.0f, 0.0f));
	stepSM->AddHero(*nogotochki->GetComponent<Hero>()); //!!!


	Entity* enemy1 = EnemyCreator::BeaverThrower(glm::vec3(0.0f, 1100.0f, 0.0f));
	stepSM->AddEnemy(*enemy1->GetComponent<Enemy>()); //!!!
	//////////////////////////////////////////////////////////////


	/////////////////////items/////////////////////
	Item pistol = ItemCreator::CreatePistol(glm::vec3(0.0f, 1800.0f, 0.0f));

	Item knife1 = ItemCreator::CreateKnife(glm::vec3(-50.0f, 300.0f, 0.0f));
	Item knife2 = ItemCreator::CreateKnife(glm::vec3(50.0f, 300.0f, 0.0f));
	Item knife3 = ItemCreator::CreateKnife(glm::vec3(-50.0f, 400.0f, 0.0f));
	Item knife4 = ItemCreator::CreateKnife(glm::vec3(50.0f, 400.0f, 0.0f));

	/////////////////////Environment/////////////////////
	UIText* txt = message->AddComponent<UIText>("destroy the beaver", glm::vec2(-.5f, 0.9f), 0.05f);
	txt->Enable();


	//to load next scene items
	Key key = ItemCreator::CreateKey(glm::vec3(-800.0f, 2000.0f, 0.0f));
	Entity* hatch = &Manager::addEntity();
	hatch->AddComponent<Transform>(glm::vec3(-1000.0f, 2000.0f, 0.0f),
		glm::vec3(100.0f, 100.0f, 1.0f));
	hatch->AddComponent<SpriteComponent>("res/Textures/Env/hatch.png");
	hatch->AddComponent<BoxCollider>(100.0f, 100.0f, false, false);
	hatch->AddComponent<LoadNextScene>();
	//


	floor1->AddComponent<Transform>(glm::vec3(0.0f, 400.0f, 0.0f));
	floor1->AddComponent<Tile>(160.0f, 400.0f, "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");

	floor2->AddComponent<Transform>(glm::vec3(-640.0f, 1600.0f, 0.0f));
	floor2->AddComponent<Tile>(800.0f, 800.0f, "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");

	//walls
	{
		wall0->AddComponent<Transform>(glm::vec3(0.0f));
		wall0->AddComponent<Tile>(160.0f, 10.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall0->AddComponent<BoxCollider>(160.0f, 10.0f, true, false);

		wall1->AddComponent<Transform>(glm::vec3(160.0f, 1200.f, 0.0f));
		wall1->AddComponent<Tile>(10.0f, 1200.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall1->AddComponent<BoxCollider>(10.0f, 1200.0f, true, false);

		wall2->AddComponent<Transform>(glm::vec3(-640.0f, 2400.f, 0.0f));
		wall2->AddComponent<Tile>(800.0f, 10.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall2->AddComponent<BoxCollider>(800.0f, 10.0f, true, false);

		wall3->AddComponent<Transform>(glm::vec3(-1440.0f, 1600.0f, 0.0f));
		wall3->AddComponent<Tile>(10.f, 800.0, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall3->AddComponent<BoxCollider>(10.f, 800.0f, true, false);

		wall4->AddComponent<Transform>(glm::vec3(-160.0f, 400.f, 0.0f));
		wall4->AddComponent<Tile>(10.0f, 400.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall4->AddComponent<BoxCollider>(10.0f, 400.0f, true, false);
		wall5->AddComponent<Transform>(glm::vec3(-790.0f, 800.f, 0.0f),
			glm::vec3(640.0f, 10.0f, 1.0f));
		wall5->AddComponent<Tile>(640.0f, 10.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall5->AddComponent<BoxCollider>(640.0f, 10.0f, true, false);

	}

	///////////////////////////////////////////////////////////////////
	vec.push_back(pistol.entity);
	vec.push_back(key.entity);
	vec.push_back(hatch);

	vec.push_back(message);

	vec.push_back(wall0);
	vec.push_back(wall1);
	vec.push_back(wall2);
	vec.push_back(wall3);
	vec.push_back(wall4);
	vec.push_back(wall5);
	vec.push_back(floor1);
	vec.push_back(floor2);

	vec.push_back(stepSys);
	vec.push_back(zubar);
	vec.push_back(harchok);
	vec.push_back(motor);
	vec.push_back(nogotochki);
	vec.push_back(enemy1);
	vec.push_back(knife1.entity);
	vec.push_back(knife2.entity);
	vec.push_back(knife3.entity);
	vec.push_back(knife4.entity);
}

void CreateScene2(std::vector<Entity*>& vec)
{
	CamComponent::SetPos(glm::vec3(0.0f));
	Entity* floor1(&Manager::addEntity());
	Entity* floor2(&Manager::addEntity());
	Entity* hallway1(&Manager::addEntity());
	Entity* hallway2(&Manager::addEntity());
	Entity* stepSys(&Manager::addEntity());
	
	Entity* wall0(&Manager::addEntity());
	Entity* wall1(&Manager::addEntity());
	Entity* wall2(&Manager::addEntity());
	Entity* wall3(&Manager::addEntity());
	Entity* wall4(&Manager::addEntity());
	Entity* wall5(&Manager::addEntity());
	Entity* wall6(&Manager::addEntity());
	Entity* wall7(&Manager::addEntity());
	Entity* wall8(&Manager::addEntity());
	Entity* wall9(&Manager::addEntity());
	Entity* wall10(&Manager::addEntity());
	Entity* wall11(&Manager::addEntity());
	Entity* wall12(&Manager::addEntity());
	Entity* wall13(&Manager::addEntity());
	Entity* wall14(&Manager::addEntity());
	Entity* wall15(&Manager::addEntity());

	StepSysManager* stepSM = stepSys->AddComponent<StepSysManager>();


	/////////////////////Environment//////////////////////////////////

	hallway1->AddComponent<Transform>(glm::vec3(0.0f, 400.0f, 0.0f));
	hallway1->AddComponent<Tile>(160.f, 400.0f, "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");

	hallway2->AddComponent<Transform>(glm::vec3(2000.0f, 1600.0f, 0.0f));
	hallway2->AddComponent<Tile>(400.f, 160.0f, "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");

	floor1->AddComponent<Transform>(glm::vec3(0.0f, 1600.0f, 0.0f));
	floor1->AddComponent<Tile>(1600.0f, 800.0f, "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");

	floor2->AddComponent<Transform>(glm::vec3(3200.f, 800.0f, 0.0f));
	floor2->AddComponent<Tile>(800.0f, 1600.0f, "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");


	//to load next scene items
	Key key = ItemCreator::CreateKey(glm::vec3(1450.0f + 1300.f, 1600.0f+200.f, 0.0f));
	Entity* hatch = &Manager::addEntity();
	hatch->AddComponent<Transform>(glm::vec3(1450.0f + 2300.f, 600.f - 1200.0f, 0.0f),
		glm::vec3(100.0f, 100.0f, 1.0f));
	hatch->AddComponent<SpriteComponent>("res/Textures/Env/hatch.png");
	hatch->AddComponent<BoxCollider>(100.0f, 100.0f, false, false);
	hatch->AddComponent<LoadNextScene>();


	{
		wall0->AddComponent<Transform>(glm::vec3(0.0f));
		wall0->AddComponent<Tile>(160.0f, 10.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall0->AddComponent<BoxCollider>(160.0f, 10.0f, true, false);

		wall1->AddComponent<Transform>(glm::vec3(-160.0f, 400.f, 0.0f));
		wall1->AddComponent<Tile>(10.0f, 400.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall1->AddComponent<BoxCollider>(10.0f, 400.0f, true, false);

		wall2->AddComponent<Transform>(glm::vec3(160.f, 400.f, 0.0f));
		wall2->AddComponent<Tile>(10.0f, 400.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall2->AddComponent<BoxCollider>(10.0f, 40.0f, true, false);

		wall3->AddComponent<Transform>(glm::vec3(960.f, 800.f, 0.f));
		wall3->AddComponent<Tile>(800.f, 10.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall3->AddComponent<BoxCollider>(800.0f, 10.0f, true, false);

		wall4->AddComponent<Transform>(glm::vec3(1600.0f, 1120.f, 0.f));
		wall4->AddComponent<Tile>(10.0f, 320.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall4->AddComponent<BoxCollider>(10.0f, 320.0f, true, false);

		wall5->AddComponent<Transform>(glm::vec3(2000.0f, 1600.f-160.f, 0.0f));
		wall5->AddComponent<Tile>(400.0f, 10.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall5->AddComponent<BoxCollider>(400.0f, 10.0f, true, false);

		wall6->AddComponent<Transform>(glm::vec3(3200.f - 800.f, 320.0f, 0.0f));
		wall6->AddComponent<Tile>(10.0f, 1120.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall6->AddComponent<BoxCollider>(10.0f, 1120.0f, true, false);

		wall7->AddComponent<Transform>(glm::vec3(3200.f, -800.f, 0.f));
		wall7->AddComponent<Tile>(800.0f, 10.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall7->AddComponent<BoxCollider>(800.0f, 10.0f, true, false);

		wall8->AddComponent<Transform>(glm::vec3(4000.f, 800.f, 0.f));
		wall8->AddComponent<Tile>(10.0f, 1600.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall8->AddComponent<BoxCollider>(10.0f, 1600.0f, true, false);

		wall9->AddComponent<Transform>(glm::vec3(3200.f, 2400.f, 0.f));
		wall9->AddComponent<Tile>(800.0f, 10.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall9->AddComponent<BoxCollider>(800.0f, 10.0f, true, false);

		wall10->AddComponent<Transform>(glm::vec3(3200.f - 800.f, 320.0f + 1760.f, 0.0f));
		wall10->AddComponent<Tile>(10.0f, 320.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall10->AddComponent<BoxCollider>(10.0f, 320.0f, true, false);

		wall11->AddComponent<Transform>(glm::vec3(2000.0f, 1600.f+160.f, 0.0f)); 
		wall11->AddComponent<Tile>(400.0f, 10.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall11->AddComponent<BoxCollider>(400.0f, 10.0f, true, false);

		wall12->AddComponent<Transform>(glm::vec3(3200.f -1600.f, 320.0f + 1760.f, 0.0f));
		wall12->AddComponent<Tile>(10.0f, 320.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall12->AddComponent<BoxCollider>(10.0f, 320.0f, true, false);

		wall13->AddComponent<Transform>(glm::vec3(0.0f, 1600.0f + 800.f, 0.0f));
		wall13->AddComponent<Tile>(1600.0f, 10.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall13->AddComponent<BoxCollider>(1600.0f, 10.0f, true, false);

		wall14->AddComponent<Transform>(glm::vec3(-1600.f, 1600.0f, 0.0f));
		wall14->AddComponent<Tile>(10.0f, 800.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall14->AddComponent<BoxCollider>(10.0f, 800.0f, true, false);

		wall15->AddComponent<Transform>(glm::vec3(-540.f - 340.f, 800.f, 0.f));
		wall15->AddComponent<Tile>(720.f, 10.0f, "res/Shaders/Basic.shader", "res/Textures/Env/wall.png");
		wall15->AddComponent<BoxCollider>(720.f, 10.0f, true, false);
	}
	////////////////////////////////////////////////////////////////

	/////////////////////Heroes and enemies/////////////////////
	Entity* zubar = HeroCreator::ZubarPrefab(glm::vec3(55.0f, 0.0f, 0.0f));
	stepSM->AddHero(*zubar->GetComponent<Hero>()); //!!!

	Entity* harchok = HeroCreator::HarchokPrefab(glm::vec3(55.0f, 100.0f, 0.0f));
	stepSM->AddHero(*harchok->GetComponent<Hero>()); //!!!


	Entity* motor = HeroCreator::MotorPrefam(glm::vec3(55.0f, 200.0f, 0.0f));
	stepSM->AddHero(*motor->GetComponent<Hero>()); //!!!

	Entity* nogotochki = HeroCreator::NogotPrefab(glm::vec3(55.0f, 300.0f, 0.0f));
	stepSM->AddHero(*nogotochki->GetComponent<Hero>()); //!!!


	Entity* enemy1 = EnemyCreator::BeaverThrower(glm::vec3(1450.0f, 1600.0f, 0.0f));
	stepSM->AddEnemy(*enemy1->GetComponent<Enemy>()); //!!!

	Entity* enemy2 = EnemyCreator::BasicBeaver(glm::vec3(1450.0f+1100.f, 200.f+1600.0f, 0.0f));
	stepSM->AddEnemy(*enemy2->GetComponent<Enemy>()); //!!!

	Entity* enemy3 = EnemyCreator::BeaverThrower(glm::vec3(1450.0f + 1200.f, 1600.0f, 0.0f));
	stepSM->AddEnemy(*enemy3->GetComponent<Enemy>()); //!!!

	Entity* eminem1 = EnemyCreator::BeaverThrower(glm::vec3(1450.0f + 2300.f, 600.f - 900.0f, 0.0f));
	stepSM->AddEnemy(*eminem1->GetComponent<Enemy>()); //!!!

	Entity* eminem2 = EnemyCreator::BasicBeaver(glm::vec3(1450.0f + 2000.f, 600.f - 1200.0f, 0.0f));
	stepSM->AddEnemy(*eminem2->GetComponent<Enemy>()); //!!!
	//////////////////////////////////////////////////////////////

	vec.push_back(key.entity);
	vec.push_back(hatch);

	vec.push_back(wall0);
	vec.push_back(wall1);
	vec.push_back(wall2);
	vec.push_back(wall3);
	vec.push_back(wall4);
	vec.push_back(wall5);
	vec.push_back(wall6);
	vec.push_back(wall7);
	vec.push_back(wall8);
	vec.push_back(wall9);
	vec.push_back(wall10);
	vec.push_back(wall11);
	vec.push_back(wall12);
	vec.push_back(wall13);
	vec.push_back(wall14);
	vec.push_back(wall15);

	vec.push_back(stepSys);

	vec.push_back(zubar);
	vec.push_back(harchok);
	vec.push_back(motor);
	vec.push_back(nogotochki);

	vec.push_back(enemy1);
	vec.push_back(enemy2);
	vec.push_back(enemy3);
	vec.push_back(eminem1);
	vec.push_back(eminem2);
}
void CreateScene3(std::vector<Entity*>& vec)
{
	CamComponent::SetPos(glm::vec3(0.0f));
	Entity* floor1(&Manager::addEntity());
	Entity* floor2(&Manager::addEntity());
	Entity* floor3(&Manager::addEntity());
	Entity* floor4(&Manager::addEntity());
	Entity* floor5(&Manager::addEntity());
	Entity* hallway1(&Manager::addEntity());
	Entity* hallway2(&Manager::addEntity());

	Entity* col1(&Manager::addEntity());
	Entity* col2(&Manager::addEntity());
	Entity* col3(&Manager::addEntity());
	Entity* col4(&Manager::addEntity());
	Entity* col5(&Manager::addEntity());
	Entity* col6(&Manager::addEntity());
	Entity* col7(&Manager::addEntity());

	Entity* wall1(&Manager::addEntity());
	Entity* wall2(&Manager::addEntity());
	Entity* wall3(&Manager::addEntity());
	Entity* wall4(&Manager::addEntity());

	Entity* stepSys(&Manager::addEntity());
	StepSysManager* stepSM = stepSys->AddComponent<StepSysManager>();

	/////////////////////ENV/////////////////////////////////
	//floor
	{
		floor1->AddComponent<Transform>(glm::vec3(0.0f, 40.0f * 8, 0.0f));
		floor1->AddComponent<Tile>(40.0f*5, 40.0f * 8, "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");

		floor2->AddComponent<Transform>(glm::vec3(40.0f*(-5), 40.0f*31, 0.0f));
		floor2->AddComponent<Tile>(40.0f*10, 40.0f*15, "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");

		floor3->AddComponent<Transform>(glm::vec3(40.0f*10, 40.0f*(31+10), 0.0f));
		floor3->AddComponent<Tile>(40.0f*10, 40.0f*5, "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");

		floor4->AddComponent<Transform>(glm::vec3(40.0f*(10+18), 40.0f * (31+15+10+6), 0.0f));
		floor4->AddComponent<Tile>(40.0f*(18), 40.0f*(6), "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");

		floor5->AddComponent<Transform>(glm::vec3(40.0f*(10 + 18+18), 40.0f*(16+15), 0.0f));
		floor5->AddComponent<Tile>(40.0f*(15), 40.0f*(15), "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");

	}
	hallway1->AddComponent<Transform>(glm::vec3(40.0f*(10+4), 40.0f*(31+15+5), 0.0f));
	hallway1->AddComponent<Tile>(40.0f*(4), 40.0f*(5), "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");

	hallway2->AddComponent<Transform>(glm::vec3(40.0f*(10+18+14), 40.0f*(31 + 15 + 1), 0.0f));
	hallway2->AddComponent<Tile>(40.0f*(4), 40.0f*(9), "res/Shaders/Basic.shader", "res/Textures/Env/FloorTexture.png");
	//walls&coliders
	{
		col1->AddComponent<Transform>(glm::vec3(40.0f * (10 + 18 + 18 + 20)/2, 40.f*(8), 0.f));
		col1->AddComponent<BoxCollider>(40.0f*(28), 40.0f*(8), true, false);

		col2->AddComponent<Transform>(glm::vec3(40.0f * (18), 40.f * (16.f + 7.f+3), 0.f));
		col2->AddComponent<BoxCollider>(40.0f*(13), 40.0f*(10), true, false);

		col3->AddComponent<Transform>(glm::vec3(40.0f * (10+15.5f), 40.0f * (31 + 10), 0.0f));
		col3->AddComponent<BoxCollider>(40.0f*(5.5f), 40.0f*(5), true, false);

		col4->AddComponent<Transform>(glm::vec3(40.0f * (10 + 18), 40.0f * (31 + 20), 0.0f));
		col4->AddComponent<BoxCollider>(40.0f*(10), 40.0f*(5), true, false);

		col5->AddComponent<Transform>(glm::vec3(40.0f * (10 + 43.5f), 40.0f * (31 + 15 + 11), 0.0f));
		col5->AddComponent<BoxCollider>(40.0f*(7.5f), 40.0f*(11), true, false);

		col6->AddComponent<Transform>(glm::vec3(40.0f*(-10), 40.0f * 8, 0.0f));
		col6->AddComponent<BoxCollider>(40.0f * 5, 40.0f * 8, true, false);

		col7->AddComponent<Transform>(glm::vec3(40.0f * (-2.5f), 40.0f * 57, 0.0f));
		col7->AddComponent<BoxCollider>(40.0f*(12.5), 40.0f*(11), true, false);

		///////////////////WALLS/////////////////////////////

		wall1->AddComponent<Transform>(glm::vec3(40.0f * (10 + 18 + 18+15)+10.f, 40.0f * (16 + 15), 0.0f));
		wall1->AddComponent<BoxCollider>(10.0f, 40.0f * (15), true, false);

		wall2->AddComponent<Transform>(glm::vec3(40.0f * (10 + 18), 40.0f * (31 + 15 + 10 + 12) +10.f, 0.0f));
		wall2->AddComponent<BoxCollider>(40.0f * (18), 10.f, true, false);

		wall3->AddComponent<Transform>(glm::vec3(0.0f, - 10.f, 0.0f));
		wall3->AddComponent<BoxCollider>(40.0f * 5, 10.f, true, false);

		wall4->AddComponent<Transform>(glm::vec3(40.0f * (-5-10) - 10.f, 40.0f * 31, 0.0f));
		wall4->AddComponent<BoxCollider>(10, 40.0f * 15, true, false);

	}

	//to load next scene items
	Key key = ItemCreator::CreateKey(glm::vec3(40.0f * (10 + 30), 40.0f * (31 + 15 + 10 + 9), 0.0f));
	Entity* hatch = &Manager::addEntity();
	hatch->AddComponent<Transform>(glm::vec3(40.0f * (10 + 18 + 27), 40.0f * (16 + 4), 0.0f),
		glm::vec3(100.0f, 100.0f, 1.0f));
	hatch->AddComponent<SpriteComponent>("res/Textures/Env/hatch.png");
	hatch->AddComponent<BoxCollider>(100.0f, 100.0f, false, false);
	hatch->AddComponent<LoadNextScene>();

	///////////////////////////////////////////////////////////
	
		/////////////////////items/////////////////////
	Item pistol1 = ItemCreator::CreatePistol(glm::vec3(40.0f * (-5), 40.0f * 26, 0.0f));
	Item pistol2 = ItemCreator::CreatePistol(glm::vec3(40.0f * (10 + 18 + 18), 40.0f * (16 + 15), 0.0f));

	Item knife1 = ItemCreator::CreateKnife(glm::vec3(-300.0f, 1300.0f, 0.0f));
	Item knife2 = ItemCreator::CreateKnife(glm::vec3(-380.0f, 1470.0f, 0.0f));

	/////////////////////Heroes and enemies/////////////////////
	Entity* zubar = HeroCreator::ZubarPrefab(glm::vec3(55.0f, 100.0f, 0.0f));
	stepSM->AddHero(*zubar->GetComponent<Hero>()); //!!!

	Entity* harchok = HeroCreator::HarchokPrefab(glm::vec3(55.0f, 100.0f, 0.0f));
	stepSM->AddHero(*harchok->GetComponent<Hero>()); //!!!


	Entity* motor = HeroCreator::MotorPrefam(glm::vec3(55.0f, 200.0f, 0.0f));
	stepSM->AddHero(*motor->GetComponent<Hero>()); //!!!

	Entity* nogotochki = HeroCreator::NogotPrefab(glm::vec3(55.0f, 300.0f, 0.0f));
	stepSM->AddHero(*nogotochki->GetComponent<Hero>()); //!!!


	Entity* enemy1 = EnemyCreator::BeaverThrower(glm::vec3(40.0f*(-2), 40.0f * (31 + 5), 0.0f));
	stepSM->AddEnemy(*enemy1->GetComponent<Enemy>()); //!!!

	Entity* enemy2 = EnemyCreator::BasicBeaver(glm::vec3(40.0f * (-3), 40.0f * (31 + 3), 0.0f));
	stepSM->AddEnemy(*enemy2->GetComponent<Enemy>()); //!!!

	Entity* enemy3 = EnemyCreator::BeaverThrower(glm::vec3(40.0f * (-1), 40.0f * (31 + 2), 0.0f));
	stepSM->AddEnemy(*enemy3->GetComponent<Enemy>()); //!!!

	Entity* enemy4 = EnemyCreator::BeaverThrower(glm::vec3(40.0f * (10 + 28), 40.0f * (31 + 15 + 10 + 9), 0.0f));
	stepSM->AddEnemy(*enemy4->GetComponent<Enemy>()); //!!!

	Entity* enemy5 = EnemyCreator::BeaverThrower(glm::vec3(40.0f * (10 + 18 + 24), 40.0f * (16 + 10), 0.0f));
	stepSM->AddEnemy(*enemy5->GetComponent<Enemy>()); //!!!

	Entity* enemy6 = EnemyCreator::BeaverThrower(glm::vec3(40.0f * (10 + 18 + 20), 40.0f * (16 + 7), 0.0f));
	stepSM->AddEnemy(*enemy6->GetComponent<Enemy>()); //!!!

	Entity* enemy7 = EnemyCreator::BeaverThrower(glm::vec3(40.0f * (10 + 18 + 17), 40.0f * (16 + 4), 0.0f));
	stepSM->AddEnemy(*enemy7->GetComponent<Enemy>()); //!!!
	//////////////////////////////////////////////////////////////

	vec.push_back(key.entity);
	vec.push_back(hatch);

	vec.push_back(floor1);
	vec.push_back(floor2);
	vec.push_back(hallway1);
	vec.push_back(stepSys);
	vec.push_back(zubar);
	vec.push_back(zubar);
	vec.push_back(harchok);
	vec.push_back(motor);
	vec.push_back(nogotochki);

	vec.push_back(enemy1);
	vec.push_back(enemy2);
	vec.push_back(enemy3);
	vec.push_back(enemy4);
	vec.push_back(enemy5);
	vec.push_back(enemy6);
	vec.push_back(enemy7);

	vec.push_back(knife1.entity);
	vec.push_back(knife2.entity);
	vec.push_back(pistol1.entity);
	vec.push_back(pistol2.entity);
}

void CreateScene4(std::vector<Entity*>& vec)
{
	Entity* finalScreen(&Manager::addEntity());
	UIText* txt = finalScreen->AddComponent<UIText>("the end", glm::vec2(-0.2f, 0.0f), 0.06f);
	txt->ChangeColor(glm::vec4(1.0f));
	txt->Enable();

	vec.push_back(finalScreen);
}