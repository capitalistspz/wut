/**
* \defgroup uvc UVC
 * \ingroup uvc
 *
 *
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif
typedef UVCRequestData UVCRequestData
typedef UVCFrame UVCFrame

typedef enum UVCStatus
{
        UVC_STATUS_BUFFER_SIZE_ERROR = -1572919,
        UVC_STATUS_USB_TRANSFER_ERROR = -1572918,
        UVC_STATUS_PH_LENGTH_ERROR = -1572917,
        UVC_STATUS_PH_FORMAT_ERROR = -1572916,
        UVC_STATUS_USB_FRAME_LOSS = -1572915,
        UVC_STATUS_WIFI_FRAME_LOSS = -1572914,
        UVC_STATUS_UNK_A = -1572913,
        UVC_STATUS_UNK_B = -1572912,
        UVC_STATUS_UNK_C = -1572911,
        UVC_STATUS_UNK_D = -1572910,
        UVC_STATUS_REQ_BUSY = -1572909,
        UVC_STATUS_WAIT_SEM_ERROR = -1572908,
        UVC_STATUS_INVALID_COMMAND = -1572907,
        UVC_STATUS_UNSUPPORTED = -1572906,
        UVC_STATUS_IPC_POOL_CREATE_ERROR = -1572905,
        UVC_STATUS_INVALID_CLIENT = -1572904,
        UVC_STATUS_UNK_F = -1572903,
        UVC_STATUS_DEVICE_CLOSE = -1572902,
        UVC_STATUS_POWER_MODE_ERROR = -1572901,
        UVC_STATUS_MAX_QUEUE = -1572900,
        UVC_STATUS_INVALID_HANDLE = -1572899,
        UVC_STATUS_NOT_EXT_IOCTLV = -1572898,
        UVC_STATUS_DEVICE_NOTREADY = -1572897,
        UVC_STATUS_DEVICE_BUSY = -1572896,
        UVC_STATUS_NOTREADY = -1572895,
        UVC_STATUS_INVALID_ARG = -1572894,
        UVC_STATUS_OK = 0
} UVCStatus;
WUT_CHECK_SIZE(UVCStatus, 4);

typedef enum UVCChannel
{
    UVC_CHANNEL_0,
    UVC_CHANNEL_1,
} UVCChannel;

typedef enum UVCValueID
{
    UVC_VALUE_U32_FRAMETIME = 0x13
} UVCValueID;

typedef enum UVCRequestID
{
    UVC_REQ_SET_VAL = 0x1,
    UVC_REQ_GET_VAL = 0x81,
    UVC_REQ_GET_MIN = 0x82,
    UVC_REQ_GET_MAX = 0x83,
    UVC_REQ_GET_RES = 0x84
} UVCReqType;

struct UVCFrame
{
    //! Signaled upon frame retrieval, error, or UVCClose called
    OSEvent completionEvent;
    //! Status upon completion
    UVCStatus asyncStatus;
    //! Number of bytes used to store frame
    int32_t bufferSize;
    //! Amount of memory allocated for frame
    uint32_t capacity;
    //! Memory allocated for frame data
    void* buffer;
};

WUT_CHECK_SIZE(UVCFrame, 0x34);

struct UVCRequestData
{
    //! See UVCValueID
    uint8_t valueId;
    //! See UVCReqType
    uint8_t requestId;
    WUT_UNKNOWN_BYTES(2);
    //! The request input/output location
    void* buffer;
    //! Number of bytes in buffer, up to 92
    uint32_t bufferSize;
    //! Number of bytes gotten out
    uint32_t realSize;
};
WUT_CHECK_SIZE(UVCRequestData, 0x10);

/**
 * Initialize UVC library
 */
UVCStatus UVCInit();

/**
 * Open UVC device
 * \param chan GamePad channel
 */
UVCStatus UVCOpen(UVCChannel chan);
/**
 * Close the UVC device
 * \param chan Gamepad channel
 * \return
 */
UVCStatus UVCClose(UVCChannel chan);

/**
 * Get a frame from the camera asynchronously
 * frame->completionEvent will
 */
UVCStatus UVCGetFrame(UVCChannel chan, UVCFrame* frame);

/**
 * Make a request to the UVC device synchronously
 */
UVCStatus UVCRequest(UVCChannel chan, UVCRequestData* req);
#ifdef __cplusplus
}
#endif
/** @} */
