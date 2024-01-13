#include "pch.h"
#include "Pagong/Graphics/Renderer.h"
#include "Pagong/Graphics/CommandList.h"
#include "Pagong/Graphics/CommandQueue.h"
#include "Pagong/Graphics/Device.h"
#include "Pagong/Graphics/Factory.h"
#include "Pagong/Graphics/SwapChain.h"

namespace Pagong::Graphics
{
	TUnique<Renderer> Renderer::Create(GraphicsApi graphicsApi)
	{
		switch (graphicsApi)
		{
		case GraphicsApi::D3D12:
			return MakeUnique<Renderer>(graphicsApi);

		case GraphicsApi::None:
		default:
			PG_ASSERT(false, "Graphics Api not supported!");
			return nullptr;
		}
	}

	Renderer::Renderer(GraphicsApi graphicsApi)
		: m_Api(graphicsApi)
	{ }

	void Renderer::Initialize(uint32 width, uint32 height, void* windowHandle)
	{
		m_Factory = Graphics::Factory::Create(m_Api);
		m_Factory->Initialize();

		m_Adapter = Graphics::Adapter::Create(m_Api);
		m_Adapter->Initialize(m_Factory);
		LogAdapter();

		m_Device = Graphics::Device::Create(m_Api);
		m_Device->Initialize(m_Adapter.get(), width, height, windowHandle);

		m_CommandList = Graphics::CommandList::Create(m_Api);
		m_CommandList->Initialize(m_Device.get());

		m_CommandQueue = Graphics::CommandQueue::Create(m_Api);
		m_CommandQueue->Initialize(m_Device.get(), (uint32)D3D12_COMMAND_LIST_TYPE_DIRECT);

		m_SwapChain = Graphics::SwapChain::Create(m_Api);
		m_SwapChain->Initialize(m_Device.get(), m_CommandQueue, m_Factory, windowHandle, width, height);
	}

	void Renderer::OnRender()
	{
		m_CommandList->Reset();

		// Indicate that the back buffer will be used as a render target.
		TShared<Resource> resource = m_SwapChain->GetCurrentRenderTarget();
		m_CommandList->TransitionBarrier(resource, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

		// Record commands.
		m_CommandList->ClearRenderTargetView(m_SwapChain, { 0.0f, 0.2f, 0.4f, 1.0f });

		// Indicate that the back buffer will now be used to present.
		m_CommandList->TransitionBarrier(resource, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

		// Must be called before execute
		m_CommandList->Close();

		// Execute the command list.
		m_CommandQueue->Execute(m_CommandList);
		
		// Present the frame.
		m_SwapChain->Present();
		
		m_CommandQueue->WaitForFence();
	}

	void Renderer::Shutdown()
	{
		m_CommandQueue->Shutdown();
		m_CommandList->Shutdown();
		m_SwapChain->Shutdown();
		m_Factory->Shutdown();
		m_Adapter->Shutdown();
		m_Device->Shutdown();
	}

	void Renderer::LogAdapter()
	{
		const wchar* description = m_Adapter->GetDescription();
		uint64 videoMemory = m_Adapter->GetDedicatedVideoMemory();
		uint64 sharedMemory = m_Adapter->GetSharedSystemMemory();
		PG_INFO("========================\nAdapter: %ls\nVRAM: %.2f MB\nShared Memory: %.2f MB\n========================",
			description, videoMemory / (1024.f * 1024.f), sharedMemory / (1024.f * 1024.f));
	}
}
