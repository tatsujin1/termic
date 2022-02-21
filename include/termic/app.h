#pragma once

#include "terminal.h"
#include "event.h"
#include "cell.h"
#include "size.h"
#include "input.h"
#include "screen.h"

#include <signals.hpp>

#include <chrono>

namespace termic
{

struct App
{
	friend void signal_received(int signum);
	friend void app_atexit();

	App(Options opts=Defaults);
	virtual ~App();

	void set_timer_interval(std::chrono::nanoseconds duration);
	void clear_timer();

	operator bool() const;

	fteng::signal<void(const event::Key)> on_key_event;
	fteng::signal<void(const event::Input)> on_input_event;
	fteng::signal<void(const event::MouseMove)> on_mouse_move_event;
	fteng::signal<void(const event::MouseButton)> on_mouse_button_event;
	fteng::signal<void(const event::MouseWheel)> on_mouse_wheel_event;

	fteng::signal<void()> on_app_start;
	fteng::signal<void(int)> on_app_exit;
	fteng::signal<void(const event::Resize)> on_resize_event;
	fteng::signal<void(const event::Focus)> on_focus_event;

	fteng::signal<void()> on_timer;

	virtual int run();

	void quit();

	Screen &screen() { return _screen; }


private:
	void shutdown(int rc=0);

	bool dispatch_event(const event::Event &e);

	void enqueue_resize_event(Size size);

private:
	Input _input;
	Screen _screen;

	int _timer_fd { 0 };

	bool _emit_resize_event { false };
	std::vector<event::Event> _internal_events;

	bool _initialized { false };

	bool _should_quit { false };
};

} // NS: termic
