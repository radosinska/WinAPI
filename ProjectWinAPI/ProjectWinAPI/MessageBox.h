#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <windows.h>


class MessageBox
{
private:
	virtual void abstractMessageBox() = 0;
public:
	static int Show(LPCSTR text, LPCSTR caption)
	{
		return ::MessageBox(NULL, text, caption, MB_OK);
	}
	static int Show(HWND owner, LPCSTR text, LPCSTR caption)
	{
		return ::MessageBox(owner, text, caption, MB_OK);
	}
	//
	// Summary:
	//     Displays a message box in front of the specified object and with the specified
	//     text, caption, buttons, icon, and default button.
	//
	// Parameters:
	//   owner:
	//     An implementation of System.Windows.Forms.IWin32Window that will own the modal
	//     dialog box.
	//
	//   text:
	//     The text to display in the message box.
	//
	//   caption:
	//     The text to display in the title bar of the message box.
	//
	//   buttons:
	//     One of the System.Windows.Forms.MessageBoxButtons values that specifies which
	//     buttons to display in the message box.
	//
	//   icon:
	//     One of the System.Windows.Forms.MessageBoxIcon values that specifies which icon
	//     to display in the message box.
	//
	//   defaultButton:
	//     One of the System.Windows.Forms.MessageBoxDefaultButton values that specifies
	//     the default button for the message box.
	//
	// Returns:
	//     One of the System.Windows.Forms.DialogResult values.
	//
	// Exceptions:
	//   T:System.ComponentModel.InvalidEnumArgumentException:
	//     buttons is not a member of System.Windows.Forms.MessageBoxButtons.-or- icon is
	//     not a member of System.Windows.Forms.MessageBoxIcon.-or- defaultButton is not
	//     a member of System.Windows.Forms.MessageBoxDefaultButton.
	//
	//   T:System.InvalidOperationException:
	//     An attempt was made to display the System.Windows.Forms.MessageBox in a process
	//     that is not running in User Interactive mode. This is specified by the System.Windows.Forms.SystemInformation.UserInteractive
	//     property.
	//static DialogResult Show(HWND owner, LPSTR text, LPSTR caption, MessageBoxButtons buttons, MessageBoxIcon icon, MessageBoxDefaultButton defaultButton);
};

#endif