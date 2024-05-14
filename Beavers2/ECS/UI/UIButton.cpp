#include "UIButton.h"

void UIButton::init()
{
	isLocked = false;
	gotClick = false;
	doCalls = false;

	timeBetweenClicks = 0.3f;
	lastClickTime = Time::GetCurrentTime();
	//////////////////from UIIcon/////////////////////
	vb = new VertexBuffer(postitions, 4 * 4 * sizeof(float));
	ib = new IndexBuffer(indices, 6);
	va = new VertexArray;

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	shader_basic = new Shader("res/Shaders/Basic.shader");
	shader_basic->Bind();

	texture->Bind();
	shader_basic->SetUniform1i("u_Texture", 0);

	color = glm::vec4(1.0f);
	shader_basic->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);

	shader_basic->Unbind();
	vb->Unbind();
	ib->Unbind();
	va->Unbind();
	texture->Unbind();
	///////////////////////
	startColor = color;
	
	entity->AddComponent<UICollider>();
	UIColl = entity->GetComponent<UICollider>();

	UIColl->width = width;
	UIColl->height = height;
	UIColl->coords = coords;

	gotClick = false;
}

void UIButton::update()
{
	UIColl->width = width;
	UIColl->height = height;
	UIColl->coords = coords;

	bool mouthOn = UIColl->GetIsCollidMouth();
	int mouseLeftState = GLFWGetKeyMouseState(GLFW_MOUSE_BUTTON_LEFT);

	
	if (!gotClick)
	{
		gotClick = (mouthOn && mouseLeftState == GLFW_PRESS);
	}

	if (gotClick && !doCalls)
	{
		lastClickTime = Time::GetCurrentTime();
		StartCalls();
	}

	if (Time::GetCurrentTime() - lastClickTime > timeBetweenClicks)
	{
		doCalls = false;
		gotClick = false;
	}
	if (!isLocked && gotClick)
	{

	}

	if (gotClick)
	{
		color = startColor - glm::vec4(0.3f);
	}
	else
	{
		color = startColor;
	}
}

void UIButton::AddCall(std::function<void()> elem)
{
	calls.push_back(elem);
}

void UIButton::SetLockedStatus(bool locked)
{
	isLocked = locked;
}

void UIButton::StartCalls()
{
	doCalls = true;
	for (auto& call : calls)
	{
		call();
	}
}

UIButton::~UIButton()
{
	UIColl->entity->destroy();
}
