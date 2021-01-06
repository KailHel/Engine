#include <chrono>
#include <thread>
#include <iostream>
#pragma once

namespace SK {
    namespace GAME {
        class IFpsController {
        private:
            //------------------------------------------------
            std::chrono::high_resolution_clock _HighClock = std::chrono::high_resolution_clock();
            //------------------------------------------------
            long long _lastTime = 0;
            long long _now = 0;
            long long _eqls = 0;
            long double _delta = 0;
            long long _count = 0;
            bool _onRender = false;
            int _Update_Rate = 60;
            int _Idle_Time = 10;
            //------------------------------------------------
            int UPD = 0;
            int LAG = 0;
            int FPS = 0;
            int L_FPS = 0;
            int L_UPD = 0;
            int L_LAG = 0;
            //------------------------------------------------
            const long long _Second = 1000000000;
            long double _Update_Interval = _Second / _Update_Rate;
            //------------------------------------------------
        public:
            bool isRunning = false;

            IFpsController() = default;

            ~IFpsController() = default;

            virtual void start();

            //------------------------------------------------
            virtual void Init() = 0;

            virtual void Update() = 0;

            virtual void Render() = 0;

            virtual void Dispose() = 0;

            //------------------------------------------------
            virtual void setFPS(int fps) {
                _Update_Rate = fps;
                _Update_Interval = _Second / _Update_Rate;
            }

            virtual int getFps() { return L_FPS; }
            virtual int getLag() { return L_LAG; }
            virtual long double getDelta() {return _eqls;}
            //------------------------------------------------
        private:
            long long _getNanoTime() {
                return _HighClock.now().time_since_epoch().count();
            }
        };
    }
}
