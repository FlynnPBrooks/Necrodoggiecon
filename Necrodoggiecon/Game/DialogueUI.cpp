#include "DialogueUI.h"

/*****************************************************************//**
 * \file   DialogueUI.cpp
 * \brief  Class that stores the UI data for dialogue as well as this, it displays it correctly.
 *
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/

/**
* Constructor - Initialises all of the UI elements including text components and backgrounds.
*/
DialogueUI::DialogueUI()
{
	textBackground = AddComponent<CSpriteComponent>();
	textBackground->LoadTextureWIC("Resources/darkBackground.png");
	nameBackground = AddComponent<CSpriteComponent>();
	nameBackground->LoadTextureWIC("Resources/darkBackground.png");
	nameTextRenderComponent = AddComponent<CTextRenderComponent>();

	//Setup Background Sprite
	auto width = Engine::windowWidth;
	auto height = Engine::windowHeight * UIHeightPercent;
	textBackground->SetRenderRect(XMUINT2(width, height));
	textBackground->SetSpriteSize(XMUINT2(width, height));
	textBackground->SetAnchor(XMFLOAT2(0, 1));
	float UIHeight = GetUIHeight();
	textBackground->SetPosition(0, UIHeight, 1);

	//Setup TextRenderComponents
	auto trc = AddComponent<CTextRenderComponent>();
	textRenderComponents.push_back(trc);

	maxCharactersInRow = width / (textRenderComponents[0]->GetCharacterSize().x * 2);
	rowHeight = textRenderComponents[0]->GetCharacterSize().y + rowPadding;
	maxRowCount = (height / rowHeight) * 0.5f;

	textRenderComponents.clear();
	for (int i = 0; i < maxRowCount; i++)
	{
		auto trc = AddComponent<CTextRenderComponent>();
		trc->SetReserveCount(maxCharactersInRow);
		textRenderComponents.push_back(trc);
	}

	for (CComponent* e : components)
		e->ui = true;
}
/**
* Function to set the passed in TextRenderComponent to the correct position using the text that it is displaying
* 
* \param textComponent
* \param row
*/
void DialogueUI::UpdateTextComponentPosition(CTextRenderComponent* textComponent, int row)
{
	int charCount = textComponent->GetText().size();
	XMUINT2 charSize = textComponent->GetCharacterDrawSize();

	int xPos = -(Engine::windowWidth * 0.5f) + (charSize.x * 0.5f * (charCount + 1));
	int yPos = (GetUIHeight() * 0.5f) - charSize.y - (rowHeight * 2 * (row));
	textComponent->SetPosition(xPos, yPos, 0);
}
/** 
* Function to calculate the height of the dialogue UI window
*/
float DialogueUI::GetUIHeight()
{
	float height = Engine::windowHeight * UIHeightPercent;
	return -(Engine::windowHeight * 0.5f) + (height * 0.5f);
}

DialogueUI::~DialogueUI()
{
}
/**
* Inherited Function - Used to add characters to the display over time
*/
void DialogueUI::Update(float deltaTime)
{
	if (!isUpdating) return;

	timer += deltaTime;
	if (timer >= 1 / charactersPerSecond)
	{
		displayingText.append(reserveText.substr(0,1));
		reserveText.erase(0, 1);
		timer = 0;
		UpdateText();
		if (reserveText.length() == 0)
			isUpdating = false;
	}
}

/**
* Function used to refresh all of the TextRenderComponents with the appropriate text
*/
void DialogueUI::UpdateText()
{
	ClearText();
	int rowsNeeded = ceil(displayingText.length() / maxCharactersInRow);
	if (rowsNeeded >= textRenderComponents.size())
		rowsNeeded = textRenderComponents.size() - 1;

	std::string tempString = displayingText;
	for (int i = 0; i <= rowsNeeded; i++)
	{
		std::string rowText = tempString.substr(0, maxCharactersInRow);
		if (rowText.empty()) continue;

		while (!rowText.empty() && rowText.back() != 0x20)
			rowText.pop_back();
		
		textRenderComponents[i]->SetText(rowText);
		UpdateTextComponentPosition(textRenderComponents[i], i + 1);
		tempString.erase(0, rowText.size());

		if (i == rowsNeeded && rowText.length() >= maxCharactersInRow)
			isUpdating = false;
	}
}
/**
 * Function used to set the text that will display in the dialogue box. 
 * 
 * \param newText - The new text (section of dialogue) that will display.
 * \param instantDisplay - Whether the text should update instantly or overtime
 */
void DialogueUI::SetText(std::string newText, bool instantDisplay)
{
	ClearText();
	displayingText = "";
	reserveText = newText;
	isUpdating = true;
	if (!instantDisplay) return;

	int rowsNeeded = ceil(reserveText.length() / maxCharactersInRow);
	if (rowsNeeded > textRenderComponents.size())
		rowsNeeded = textRenderComponents.size() - 1;


	for (int i = 0; i <= rowsNeeded; i++)
	{
		std::string rowText = reserveText.substr(0, maxCharactersInRow);
		while (!rowText.empty() && rowText.back() != 0x20)
			rowText.pop_back();
		
		textRenderComponents[i]->SetText(rowText);
		UpdateTextComponentPosition(textRenderComponents[i], i + 1);
		reserveText.erase(0, rowText.size());
		displayingText.append(rowText);
	}
	isUpdating = false;
}
/**
 * Function used to set the name text above the dialogue box.
 * 
 * \param newName - The new name that should be displayed.
 */
void DialogueUI::SetName(std::string newName)
{
	nameText = newName;
	nameTextRenderComponent->SetText(nameText);

	auto charSize = nameTextRenderComponent->GetCharacterDrawSize();
	int width = charSize.x * (nameText.length() + 1);
	int height = charSize.y * 1.5f;
	nameBackground->SetRenderRect(XMUINT2(width, height));
	nameBackground->SetSpriteSize(XMUINT2(width, height));
	nameBackground->SetAnchor(XMFLOAT2(0, 1));

	int xPos = -(Engine::windowWidth * 0.5f) + (charSize.x * 0.5f * (nameText.length() + 1));
	int uiHeight = (GetUIHeight() * 0.5f - height * 0.5f) + 2; 
	nameBackground->SetPosition(xPos, uiHeight, 1);

	nameTextRenderComponent->SetPosition(xPos, uiHeight, 0);
}
/**
 * Function used to clear the text being displayed in the dialogue box.
 * 
 */
void DialogueUI::ClearText()
{
	
	for (CTextRenderComponent* t : textRenderComponents)
	{
		t->SetText("");
	}
}

void DialogueUI::Complete()
{
	isUpdating = false;
	displayingText.append(reserveText);
	UpdateText();
}
/**
 * Function used to instantly display as much dialogue from the current section of dialogue on the screen as possible.
 * 
 */
void DialogueUI::CompletePage()
{
	ClearText();
	displayingText.append(reserveText);
	reserveText = displayingText;
	displayingText = "";
	int rowsNeeded = ceil(reserveText.length() / maxCharactersInRow);
	if (rowsNeeded >= textRenderComponents.size())
		rowsNeeded = textRenderComponents.size() - 1;

	for (int i = 0; i <= rowsNeeded; i++)
	{
		std::string rowText = reserveText.substr(0, maxCharactersInRow);
		textRenderComponents[i]->SetText(rowText);
		UpdateTextComponentPosition(textRenderComponents[i], i + 1);
		reserveText.erase(0, maxCharactersInRow);
		displayingText.append(rowText);
	}
	isUpdating = false;
}
/**
 * Function used to check whether the current section of dialogue is complete.
 * 
 *
 */
bool DialogueUI::IsComplete()
{
	if (!isUpdating && reserveText.size() == 0)
		return true;
	return false;
}
/**
 * Function used to advance the current section of dialogue. Should only be called once the dialogue box is full.
 * 
 */
void DialogueUI::Advance()
{
	displayingText.clear();
	isUpdating = true;
}
/**
 * Function used to enable and disable drawing of the dialogue box.
 * 
 * \param shouldDraw - Whether the dialogue UI should draw or not.
 */
void DialogueUI::ToggleDrawing(bool shouldDraw)
{
	for (CComponent* e : components)
		e->shouldDraw = shouldDraw;
}
