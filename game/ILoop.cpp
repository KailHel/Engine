#include "GLFW/glfw3.h"
#include "ILoop.h"

void SK::GAME::IFpsController::start() {
	_lastTime = _getNanoTime();
	isRunning = true;
	Init();
start:
	_now = _getNanoTime();
	_eqls = _now - _lastTime;
	_lastTime = _now;
	_delta += (_eqls / _Update_Interval);
	_count += _eqls;
	while (_delta > 1) {
		_delta -= 1;
		UPD++;
		if (_onRender) {
			LAG++;
		}
		else {
			_onRender = true;
		}
		Update();
	}
	if (_onRender) {
		FPS++;
		_onRender = false;
		Render();
	}
	else {
		std::this_thread::sleep_for(std::chrono::milliseconds(_Idle_Time));
	}
	if (_count >= _Second) {
		_count = 0;
		L_FPS = FPS;
		L_UPD = UPD;
		L_LAG = LAG;
		UPD = 0;
		FPS = 0;
		LAG = 0;
	}
	if (!isRunning) goto end;
	goto start;
end:
	Dispose();
	exit(0);
}