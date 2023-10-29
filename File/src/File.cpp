//--------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "File.h"

namespace Azul
{

	bool File::IsHandleValid(File::Handle fh) noexcept
	{
		if (INVALID_HANDLE_VALUE == fh)
		{
			return false;
		}

		return true;
	}

	File::Error File::Open(File::Handle& fh, const char* const fileName, File::Mode mode) noexcept
	{
		//default error
		File::Error status = File::Error::OPEN_FAIL;	

		switch (mode)
		{
			case File::Mode::WRITE:
				fh = CreateFile(fileName, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
				if (IsHandleValid(fh))
				{
					status =  File::Error::SUCCESS;
				}
			break;

			case File::Mode::READ:
				fh = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_ALWAYS, 0, NULL);
				if (IsHandleValid(fh))
				{
					status = File::Error::SUCCESS;
				}
				break;

			case File::Mode::READ_WRITE:
				fh = CreateFile(fileName, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
				if (IsHandleValid(fh))
				{
					status =  File::Error::SUCCESS;
				}
				break;
		}

		return 	status;
	}

	File::Error File::Close(File::Handle &fh) noexcept
	{
		//default error
		File::Error status = File::Error::CLOSE_FAIL;

		if (IsHandleValid(fh))
		{
			DWORD flag;
			bool info = GetHandleInformation(fh, &flag);
			if (info)
			{
				CloseHandle(fh);
				fh = INVALID_HANDLE_VALUE;
				status = File::Error::SUCCESS;
			}
		}

		return 	status;
	}

	File::Error File::Write(File::Handle fh, const void* const buffer, const DWORD inSize) noexcept
	{
		//default error
		File::Error status = File::Error::WRITE_FAIL;

		if (WriteFile(fh, buffer, inSize, 0, NULL))
		{
			status = File::Error::SUCCESS;
		}

		return 	status;
	}

	File::Error File::Read(File::Handle fh, void* const buffer, const DWORD inSize) noexcept
	{
		//default error
		File::Error status = File::Error::READ_FAIL;

		if (ReadFile(fh, buffer, inSize, 0, NULL))
		{
			status = File::Error::SUCCESS;
		}

		return 	status;
	}

	File::Error File::Seek(File::Handle fh, File::Position location, int offset) noexcept
	{
		//default error
		File::Error status = File::Error::SEEK_FAIL;
		DWORD seekError;

		switch (location)
		{
		case File::Position::BEGIN:
			if (SetFilePointer(fh, offset, NULL, FILE_BEGIN) != INVALID_SET_FILE_POINTER)
			{
				seekError = GetLastError();
				if (seekError != ERROR_NEGATIVE_SEEK)
				{
					status = File::Error::SUCCESS;
				}
			}
			break;

		case File::Position::CURRENT:
			if(SetFilePointer(fh, offset, NULL, FILE_CURRENT) != INVALID_SET_FILE_POINTER)
			{
				seekError = GetLastError();
				if (seekError != ERROR_NEGATIVE_SEEK)
				{
					status = File::Error::SUCCESS;
				}
			}
			break;

		case File::Position::END:
			if (SetFilePointer(fh, offset, NULL, FILE_END) != INVALID_SET_FILE_POINTER)
			{
				seekError = GetLastError();
				if (seekError != ERROR_NEGATIVE_SEEK)
				{
					status = File::Error::SUCCESS;
				};
			}
			break;
		}

		return 	status;
	}

	File::Error File::Tell(File::Handle fh, DWORD& offset) noexcept
	{
		//default error
		File::Error status = File::Error::TELL_FAIL;

		if (IsHandleValid(fh))
		{
			offset = SetFilePointer(fh, 0, NULL, FILE_CURRENT);
			status = File::Error::SUCCESS;
		}
		

		return 	status;
	}

	File::Error File::Flush(File::Handle fh) noexcept
	{
		//default error
		File::Error status = File::Error::FLUSH_FAIL;

		if (FlushFileBuffers(fh))
		{
			status = File::Error::SUCCESS;
		}

		return status;
	}

}

// ---  End of File ---------------
