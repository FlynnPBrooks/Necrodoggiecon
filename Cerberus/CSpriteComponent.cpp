#include "CSpriteComponent.h"
#include "Engine.h"
#include "Utility/AssetManager/AssetManager.h"

void CSpriteComponent::SetRenderRect(XMUINT2 newSize)
{
	renderRect = newSize;

	if (textureLoaded)
	{
		texture->material.Material.textureRect = renderRect;
		Engine::deviceContext->UpdateSubresource(texture->materialConstantBuffer, 0, nullptr, &texture->material, 0, 0);	//Could be done once per update if a change has happened instead of here
	}
}

XMUINT2 CSpriteComponent::GetRenderRect()
{
	return renderRect;
}

void CSpriteComponent::SetTextureOffset(XMFLOAT2 newOffset)
{
	textureOffset = newOffset;

	if (textureLoaded)
	{
		texture->material.Material.textureOffset = textureOffset;
		Engine::deviceContext->UpdateSubresource(texture->materialConstantBuffer, 0, nullptr, &texture->material, 0, 0);	//Could be done once per update if a change has happened instead of here
	}
}

XMFLOAT2 CSpriteComponent::GetTextureOffset()
{
	return textureOffset;
}

CSpriteComponent::CSpriteComponent()
{
	shouldUpdate = false;
	shouldDraw = true;

	mesh = AssetManager::GetDefaultMesh();
	texture = nullptr;
}

HRESULT CSpriteComponent::LoadTexture(std::string filePath)
{
	texture = AssetManager::GetTexture(filePath);

	if (texture == nullptr)
		return S_FALSE;

	textureLoaded = true;
	renderRect = texture->textureSize;
	spriteSize = texture->textureSize;

	return S_OK;
}

void CSpriteComponent::Update(float deltaTime)
{

}

void CSpriteComponent::Draw(ID3D11DeviceContext* context)
{
	if (!textureLoaded)
	{
		Debug::LogError("Texture not loaded for CSpriteComponent.");
		return;
	}

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Engine::deviceContext->IASetVertexBuffers(0, 1, &mesh->vertexBuffer, &stride, &offset);

	// Set index buffer
	Engine::deviceContext->IASetIndexBuffer(mesh->indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	Engine::deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Engine::deviceContext->PSSetConstantBuffers(1, 1, &texture->materialConstantBuffer);

	context->PSSetShaderResources(0, 1, &texture->textureResourceView);
	context->PSSetSamplers(0, 1, &texture->samplerLinear);
	
	context->DrawIndexed(6, 0, 0);
}

CSpriteComponent::~CSpriteComponent()
{
}

XMFLOAT4X4 CSpriteComponent::GetTransform()
{
	//Could check for changes and then recalculate world if changes have happened

	XMMATRIX mat = XMMatrixScaling(scale.x * spriteSize.x, scale.y * spriteSize.y, scale.z)
		* XMMatrixRotationRollPitchYaw(0, 0, rotation)
		* XMMatrixTranslation(position.x, position.y, position.z);

	XMStoreFloat4x4(&world, mat);
	return world;
}
