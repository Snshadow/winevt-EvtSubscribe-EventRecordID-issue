#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <winevt.h>

#pragma comment(lib, "wevtapi.lib")

#define ARRAY_SIZE 10

DWORD EnumerateResults(EVT_HANDLE hResults);
DWORD PrintPullEvent(EVT_HANDLE hEvent);

void GetPullEvent(LPCWSTR pwsPath, LPCWSTR pwsQuery)
{
	DWORD status = ERROR_SUCCESS;
	EVT_HANDLE hSubscription = NULL;
	HANDLE aWaitHandles[2];
	DWORD dwWait = 0;

	// Get a handle for console input, so you can break out of the loop.
	aWaitHandles[0] = GetStdHandle(STD_INPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == aWaitHandles[0])
	{
		wprintf(L"GetStdHandle failed with %lu.\n", GetLastError());
		goto cleanup;
	}

	// Get a handle to a manual reset event object that the subscription will signal
	// when events become available that match your query criteria.
	aWaitHandles[1] = CreateEvent(NULL, TRUE, TRUE, NULL);
	if (NULL == aWaitHandles[1])
	{
		wprintf(L"CreateEvent failed with %lu.\n", GetLastError());
		goto cleanup;
	}

	// Subscribe to events.
	hSubscription = EvtSubscribe(NULL, aWaitHandles[1], pwsPath, pwsQuery, NULL, NULL, NULL, EvtSubscribeStartAtOldestRecord);
	if (NULL == hSubscription)
	{
		status = GetLastError();

		if (ERROR_EVT_CHANNEL_NOT_FOUND == status)
			wprintf(L"Channel %s was not found.\n", pwsPath);
		else if (ERROR_EVT_INVALID_QUERY == status)
			wprintf(L"The query %s was not found.\n", pwsQuery);
		else
			wprintf(L"EvtSubscribe failed with %lu.\n", status);

		goto cleanup;
	}

	wprintf(L"Press 'q' to quit(will quit after all events are handled with EvtNext).\n");

	// Loop until the user presses 'q' or there is an error.
	while (true)
	{
		dwWait = WaitForMultipleObjects(sizeof(aWaitHandles) / sizeof(HANDLE), aWaitHandles, FALSE, INFINITE);
		if (0 == dwWait - WAIT_OBJECT_0) {
			INPUT_RECORD Record[128];
			DWORD dwRecordsRead = 0;
			KEY_EVENT_RECORD KeyEvent;
			
			if (ReadConsoleInput(aWaitHandles[0], Record, 128, &dwRecordsRead))
			{
				for (DWORD i = 0; i < dwRecordsRead; ++i)
				{
					if (KEY_EVENT == Record[i].EventType)
					{
						KeyEvent = Record[i].Event.KeyEvent;
						// virtual key code for 'Q' = 0x51
						if (0x51 == KeyEvent.wVirtualKeyCode)
							goto cleanup;
					}
				}
			}
		}
		else if (1 == dwWait - WAIT_OBJECT_0) // Query results
		{
			if (ERROR_NO_MORE_ITEMS != (status = EnumerateResults(hSubscription)))
			{
				break;
			}

			ResetEvent(aWaitHandles[1]);
		}
		else
		{
			if (WAIT_FAILED == dwWait)
			{
				wprintf(L"WaitForMultipleObjects failed with %lu\n", GetLastError());
			}
			break;
		}
	}

cleanup:

	if (hSubscription)
		EvtClose(hSubscription);

	if (aWaitHandles[0])
		CloseHandle(aWaitHandles[0]);

	if (aWaitHandles[1])
		CloseHandle(aWaitHandles[1]);
}

// Enumerate the events in the result set.
DWORD EnumerateResults(EVT_HANDLE hResults)
{
	DWORD status = ERROR_SUCCESS;
	EVT_HANDLE hEvents[ARRAY_SIZE];
	DWORD dwReturned = 0;

	while (true)
	{
		// Get a block of events from the result set.
		if (!EvtNext(hResults, ARRAY_SIZE, hEvents, INFINITE, 0, &dwReturned))
		{
			if (ERROR_NO_MORE_ITEMS != (status = GetLastError()))
			{
				wprintf(L"EvtNext failed with %lu\n", status);
			}

			goto cleanup;
		}

		// For each event, call the PrintEvent function which renders the
		// event for display.
		for (DWORD i = 0; i < dwReturned; i++)
		{
			if (ERROR_SUCCESS == (status = PrintPullEvent(hEvents[i])))
			{
				EvtClose(hEvents[i]);
				hEvents[i] = NULL;
			}
			else
			{
				goto cleanup;
			}
		}
	}

cleanup:

	// Closes any events in case an error occurred above.
	for (DWORD i = 0; i < dwReturned; i++)
	{
		if (NULL != hEvents[i])
			EvtClose(hEvents[i]);
	}

	return status;
}

// Render the pull event as an XML string and print it.
DWORD PrintPullEvent(EVT_HANDLE hEvent)
{
	DWORD status = ERROR_SUCCESS;
	DWORD dwBufferSize = 0;
	DWORD dwBufferUsed = 0;
	DWORD dwPropertyCount = 0;
	LPWSTR pRenderedContent = NULL;

	// The EvtRenderEventXml flag tells EvtRender to render the event as an XML string.
	if (!EvtRender(NULL, hEvent, EvtRenderEventXml, dwBufferSize, pRenderedContent, &dwBufferUsed, &dwPropertyCount))
	{
		if (ERROR_INSUFFICIENT_BUFFER == (status = GetLastError()))
		{
			dwBufferSize = dwBufferUsed;
			pRenderedContent = (LPWSTR)malloc(dwBufferSize);
			if (pRenderedContent)
			{
				EvtRender(NULL, hEvent, EvtRenderEventXml, dwBufferSize, pRenderedContent, &dwBufferUsed, &dwPropertyCount);
			}
			else
			{
				wprintf(L"malloc failed\n");
				status = ERROR_OUTOFMEMORY;
				goto cleanup;
			}
		}

		if (ERROR_SUCCESS != (status = GetLastError()))
		{
			wprintf(L"EvtRender failed with %d\n", GetLastError());
			goto cleanup;
		}
	}

	wprintf(L"\n\n%s", pRenderedContent);

cleanup:

	if (pRenderedContent)
		free(pRenderedContent);

	return status;
}
