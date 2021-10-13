#pragma once
#include <functional>
#include <thread>
#include <list>
#include <mutex>
#include <memory>
#include <condition_variable>

namespace WORKERS {

	class WorkerThread
	{

	public:
		WorkerThread();
		~WorkerThread();
		void doAsync(const std::function<void()>& t);


		void doSync(const std::function<void()>& t);

		void wait();
		void stop();

	private:
		void startThread();
	private:
		std::condition_variable itemInQueue;
		std::mutex mutex;
		std::unique_ptr<std::thread> thread;
		std::list<std::function<void()>> tasks;
		volatile bool isRunning;
	};
}