#pragma once
#include <wut.h>
#include <padscore/wpad.h>

/**
 * \defgroup padscore_kpad KPAD
 * \ingroup padscore
 *
 * KPAD is a high-level library over WPAD.
 *
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

//! Wii Remote channel.
typedef enum WPADChan KPADChan;
//! Data format.
typedef enum WPADDataFormat KPADDataFormat;
//! Extension type.
typedef enum WPADExtensionType KPADExtensionType;
//! MotionPlus Mode.
typedef enum WPADMplsMode KPADMplsMode;

typedef struct KPADStatus KPADStatus;
typedef struct KPADVec2D KPADVec2D;
typedef struct KPADVec3D KPADVec3D;

//! Error.
typedef enum KPADError
{
   //! No error occurred, and data was written to the buffers.
   KPAD_ERROR_OK                 = 0,
   //! There was no sample new data available to write.
   KPAD_ERROR_NO_SAMPLES         = -1,
   //! The requested controller or channel was invalid.
   KPAD_ERROR_INVALID_CONTROLLER = -2,
   //! WPAD is uninitialized, shouldn't happen unless WPADShutdown() is manually called
   KPAD_ERROR_WPAD_UNINIT        = -3,
   //! KPAD channel is busy, perhaps being accessed by another thread
   KPAD_ERROR_BUSY               = -4,
   //! KPAD is uninitialized, need to call KPADInit()
   KPAD_ERROR_UNINITIALIZED      = -5,
} KPADError;

//! 2D vector.
struct KPADVec2D
{
   //! x.
   float x;
   //! y.
   float y;
};
WUT_CHECK_OFFSET(KPADVec2D, 0x00, x);
WUT_CHECK_OFFSET(KPADVec2D, 0x04, y);
WUT_CHECK_SIZE(KPADVec2D, 0x08);

//! 3D vector.
struct KPADVec3D
{
   //! x.
   float x;
   //! y.
   float y;
   //! z.
   float z;
};
WUT_CHECK_OFFSET(KPADVec3D, 0x00, x);
WUT_CHECK_OFFSET(KPADVec3D, 0x04, y);
WUT_CHECK_OFFSET(KPADVec3D, 0x08, z);
WUT_CHECK_SIZE(KPADVec3D, 0x0C);

//! A structure containing the Wii Remote data.
struct KPADStatus
{
   //! Indicates what KPADButtons are held down.
   uint32_t hold;

   //! Indicates what KPADButtons have been pressed since last sample.
   uint32_t trigger;

   //! Indicates what KPADButtons have been released since last sample.
   uint32_t release;

   //! Indicates the value of the acceleration sensor.
   KPADVec3D acc;

   //! Indicates the magnitude of acceleration.
   float accMagnitude;

   //! Indicates the variation in acceleration.
   float accVariation;

   //! Indicates the position where the Wii Remote is pointing.
   KPADVec2D pos;

   WUT_UNKNOWN_BYTES(3 * 4);

   //! Angle.
   KPADVec2D angle;

   WUT_UNKNOWN_BYTES(8 * 4);

   //! Value from KPADExtensionType.
   uint8_t extensionType;

   //! Value from KPADError.
   int8_t error;

   //! Validity of the result.
   int8_t posValid;

   //! Value from KPADDataFormat.
   uint8_t format;

   //! Extension data, check with extensionType to see what is valid to read.
   union
   {
      //! Structure to use when extension type is set to \link WPAD_EXT_NUNCHUK \endlink.
      struct
      {
         //! Position of the analog stick.
         KPADVec2D stick;
         //! Indicates the value of the acceleration sensor.
         KPADVec3D acc;
         //! Indicates the magnitude of acceleration.
         float accMagnitude;
         //! Indicates the variation in acceleration.
         float accVariation;
         //! Indicates what buttons are held down.
         uint32_t hold;
         //! Indicates what buttons have been pressed since last sample.
         uint32_t trigger;
         //! Indicates what buttons have been released since last sample.
         uint32_t release;
      } nunchuk;

      //! Structure to use when extension type is set to \link WPAD_EXT_CLASSIC \endlink.
      struct
      {
         //! Indicates what buttons are held down.
         uint32_t hold;
         //! Indicates what buttons have been pressed since last sample.
         uint32_t trigger;
         //! Indicates what buttons have been released since last sample.
         uint32_t release;
         //! Position of left analog stick.
         KPADVec2D leftStick;
         //! Position of right analog stick.
         KPADVec2D rightStick;
         //! Left trigger.
         float leftTrigger;
         //! Right trigger.
         float rightTrigger;
      } classic;

      //! Structure to use when extension type is set to \link WPAD_EXT_PRO_CONTROLLER \endlink.
      struct
      {
         //! Indicates what buttons are held down.
         uint32_t hold;
         //! Indicates what buttons have been pressed since last sample.
         uint32_t trigger;
         //! Indicates what buttons have been released since last sample.
         uint32_t release;
         //! Position of left analog stick.
         KPADVec2D leftStick;
         //! Position of right analog stick.
         KPADVec2D rightStick;
         //! Is charging flag.
         int32_t charging;
         //! Is wired flag.
         int32_t wired;
      } pro;

      WUT_UNKNOWN_BYTES(20 * 4);
   };

   WUT_UNKNOWN_BYTES(16 * 4);
};
WUT_CHECK_OFFSET(KPADStatus, 0x00, hold);
WUT_CHECK_OFFSET(KPADStatus, 0x04, trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x08, release);
WUT_CHECK_OFFSET(KPADStatus, 0x0C, acc);
WUT_CHECK_OFFSET(KPADStatus, 0x18, accMagnitude);
WUT_CHECK_OFFSET(KPADStatus, 0x1C, accVariation);
WUT_CHECK_OFFSET(KPADStatus, 0x20, pos);
WUT_CHECK_OFFSET(KPADStatus, 0x34, angle);
WUT_CHECK_OFFSET(KPADStatus, 0x5C, extensionType);
WUT_CHECK_OFFSET(KPADStatus, 0x5D, error);
WUT_CHECK_OFFSET(KPADStatus, 0x5E, posValid);
WUT_CHECK_OFFSET(KPADStatus, 0x5F, format);
// For WPAD_EXT_NUNCHUK
WUT_CHECK_OFFSET(KPADStatus, 0x60, nunchuk.stick);
WUT_CHECK_OFFSET(KPADStatus, 0x68, nunchuk.acc);
WUT_CHECK_OFFSET(KPADStatus, 0x74, nunchuk.accMagnitude);
WUT_CHECK_OFFSET(KPADStatus, 0x78, nunchuk.accVariation);
WUT_CHECK_OFFSET(KPADStatus, 0x7C, nunchuk.hold);
WUT_CHECK_OFFSET(KPADStatus, 0x80, nunchuk.trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x84, nunchuk.release);
// For WPAD_EXT_CLASSIC
WUT_CHECK_OFFSET(KPADStatus, 0x60, classic.hold);
WUT_CHECK_OFFSET(KPADStatus, 0x64, classic.trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x68, classic.release);
WUT_CHECK_OFFSET(KPADStatus, 0x6C, classic.leftStick);
WUT_CHECK_OFFSET(KPADStatus, 0x74, classic.rightStick);
WUT_CHECK_OFFSET(KPADStatus, 0x7C, classic.leftTrigger);
WUT_CHECK_OFFSET(KPADStatus, 0x80, classic.rightTrigger);
// For WPAD_EXT_PRO_CONTROLLER
WUT_CHECK_OFFSET(KPADStatus, 0x60, pro.hold);
WUT_CHECK_OFFSET(KPADStatus, 0x64, pro.trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x68, pro.release);
WUT_CHECK_OFFSET(KPADStatus, 0x6C, pro.leftStick);
WUT_CHECK_OFFSET(KPADStatus, 0x74, pro.rightStick);
WUT_CHECK_OFFSET(KPADStatus, 0x7C, pro.charging);
WUT_CHECK_OFFSET(KPADStatus, 0x80, pro.wired);
WUT_CHECK_SIZE(KPADStatus, 0xF0);

typedef WPADConnectCallback KPADConnectCallback;

/**
 * Initialises the KPAD library for use.
 */
void
KPADInit();

/**
 * Cleans up and frees the KPAD library.
 */
void
KPADShutdown();

/**
 * Read data from the desired controller.
 *
 * \param chan
 * The channel of the controller to read from.
 *
 * \param data
 * The KPADStatus to fill.
 *
 * \param size
 * The maximum number of data to read.
 *
 * \return
 * The number of data read.
 */
int32_t
KPADRead(KPADChan chan,
         KPADStatus *data,
         uint32_t size);

/**
 * Read data from the desired controller.
 *
 * \param chan
 * The channel of the controller to read from.
 *
 * \param data
 * The KPADStatus to fill.
 *
 * \param size
 * The maximum number of data to read.
 *
 * \param error
 * A pointer to an error code.
 *
 * \return
 * The number of data read.
 */
int32_t
KPADReadEx(KPADChan chan,
           KPADStatus *data,
           uint32_t size,
           KPADError *error);

/**
 * Set the maximum amount of controllers which can be connected to the system.
 *
 * \param maxControllers
 * The maximum amount of controllers. Must be \c 4 or \c 7.
 *
 * \return
 * 0 on success.
 */
int32_t
KPADSetMaxControllers(uint32_t maxControllers);

/**
 * Get the maximum amount of controllers which can be connected to the system.
 *
 * \return
 * The maximum amount of controllers.
 */
uint32_t
KPADGetMaxControllers(void);

/**
 * Get the maximum amount of controllers which can be connected, as reported by IOS-PAD.
 *
 * \return
 * The maximum amount of controllers.
 */
uint32_t
KPADGetGameMaxControllers(void);

/**
 * Set a callback for when a controller connection status changes.
 *
 * \param chan
 * The channel of the controller to set a callback for.
 *
 * \param callback
 * Pointer to a callback function.
 *
 * \return
 * The previous connect callback.
 */
KPADConnectCallback
KPADSetConnectCallback(KPADChan chan,
                       KPADConnectCallback callback);

/**
 * Sets MotionPlus for the controller in specified mode
 * 
 * \param mode
 * The MotionPlus mode which should be used, the mode may be ignored and a different mode used,
 * usually because the required extension is not connected. Make sure to check result with
 * \link KPADGetMplsStatus \endlink
 */
void
KPADEnableMpls(KPADChan channel,
               KPADMplsMode mode);

/**
 * Disables MotionPlus for the controller
 */
void
KPADDisableMpls(KPADChan channel);

/**
 * Get MotionPlus mode
 *
 * identical to \ref WPADiGetMplsStatus
 */
KPADMplsMode
KPADGetMplsStatus(KPADChan chan);

/**
 * Enable IR pointing
 */
void
KPADEnableDPD(KPADChan chan);

/**
 * Disable IR pointing
 */
void
KPADDisableDPD(KPADChan chan);

#ifdef __cplusplus
}
#endif

/** @} */
