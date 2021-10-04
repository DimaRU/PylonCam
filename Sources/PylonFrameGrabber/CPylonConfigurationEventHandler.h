#ifndef CPylonConfigurationEventHandler_h
#define CPylonConfigurationEventHandler_h

#include <pylon/ConfigurationEventHandler.h>

namespace Pylon
{
    class CInstantCamera;

    class CPylonConfigurationEventHandler : public CConfigurationEventHandler
    {
	private:
		const void *object;
		EventCallback eventCallback;
    public:
		CPylonConfigurationEventHandler(const void * object, EventCallback eventCallback)
		{
			this->object = object;
			this->eventCallback = eventCallback;
		}
		void OnAttach( CInstantCamera& camera ) { eventCallback(object, cameraAttach, nullptr); }
		void OnAttached( CInstantCamera& camera ) { eventCallback(object, cameraAttached, nullptr); }
		void OnOpen( CInstantCamera& camera ) { eventCallback(object, cameraOpen, nullptr); }
		void OnOpened( CInstantCamera& camera ) { eventCallback(object, cameraOpened, nullptr); }
		void OnGrabStart( CInstantCamera& camera ) { eventCallback(object, cameraGrabStart, nullptr); }
		void OnGrabStarted( CInstantCamera& camera ) { eventCallback(object, cameraGrabStarted, nullptr); }
		void OnGrabStop( CInstantCamera& camera ) { eventCallback(object, cameraGrabStop, nullptr); }
		void OnGrabStopped( CInstantCamera& camera ) { eventCallback(object, cameraGrabStopped, nullptr); }
		void OnClose( CInstantCamera& camera ) { eventCallback(object, cameraClose, nullptr); }
		void OnClosed( CInstantCamera& camera ) { eventCallback(object, cameraClosed, nullptr); }
		void OnDestroy( CInstantCamera& camera ) { eventCallback(object, cameraDestroy, nullptr); }
		void OnDestroyed( CInstantCamera& camera ) { eventCallback(object, cameraDestroyed, nullptr); }
		void OnDetach( CInstantCamera& camera ) { eventCallback(object, cameraDetach, nullptr); }
		void OnDetached( CInstantCamera& camera ) { eventCallback(object, cameraDetached, nullptr); }
		void OnGrabError( CInstantCamera& camera, const char* errorMessage ) { eventCallback(object, cameraGrabError, errorMessage); }
		void OnCameraDeviceRemoved( CInstantCamera& camera ) { eventCallback(object, cameraDeviceRemoved, nullptr); }
    };
}

#endif /* CPylonConfigurationEventHandler_h */
