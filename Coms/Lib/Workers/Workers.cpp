// Workers.cpp : Hiermit werden die Funktionen für die statische Bibliothek definiert.
//

#include "pch.h"
#include "framework.h"
#include "WorkerThread.h"
// TODO: Dies ist ein Beispiel für eine Bibliotheksfunktion.
void fnWorkers()
{
}


WORKERS::WorkerThread* CreateWorker() {
	return new WORKERS::WorkerThread();
}