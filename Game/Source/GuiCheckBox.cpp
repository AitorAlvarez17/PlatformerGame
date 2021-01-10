#include "GuiCheckBox.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::CHECKBOX, id)
{
	this->bounds = bounds;
	this->checkedBounds = { bounds.x + 15, bounds.y + 15, 50, 50 };
	this->text = text;
}

GuiCheckBox::~GuiCheckBox()
{
}

bool GuiCheckBox::Update(Input* input, float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		int mouseX, mouseY;
		input->GetMousePosition(mouseX, mouseY);

		// Check collision between mouse and button bounds
		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
		{
			state = GuiControlState::FOCUSED;

			if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				checked = !checked;
				NotifyObserver();
			}
		}
		else state = GuiControlState::NORMAL;
	}

	return false;
}

bool GuiCheckBox::Draw(Render* render)
{
	// Draw the right button depending on state
	switch (state)
	{
	case GuiControlState::DISABLED:
	{
		if (checked) render->DrawRectangle(bounds, { 100, 100, 100, 255 });
		else render->DrawRectangle(bounds, { 0, 108, 107, 200 });
	} break;
	case GuiControlState::NORMAL:
	{
		if (checked)
		{
			render->DrawRectangle(bounds, { 46, 108, 107, 255 });//BG QUAD -
			render->DrawRectangle(checkedBounds, { 0, 255, 255, 255 });//LITTLE QUAD - 
		}
		else render->DrawRectangle(bounds, { 46, 108, 107, 255 });
	} break;
	case GuiControlState::FOCUSED:
		if (checked)
		{
			render->DrawRectangle(bounds, { 46, 108, 107, 255 });//IDLE
			render->DrawRectangle(checkedBounds, { 255, 255, 0, 255 });//YELLOW
		}
		else render->DrawRectangle(bounds, { 255, 255, 0, 255 });;//YELLOW
		break;
	case GuiControlState::PRESSED:
		if (checked)
		{
			render->DrawRectangle(bounds, { 46, 108, 107, 255 });//IDLE
			render->DrawRectangle(checkedBounds, { 255, 0, 255, 255 });//PURPLE
		}
		else render->DrawRectangle(bounds, { 255, 0, 255, 255 });//PURPLE
		break;
	case GuiControlState::SELECTED: render->DrawRectangle(bounds, { 0, 255, 0, 255 });
		break;
	default:
		break;
	}

	return false;
}
