#include "sfmltest.h"

sfmltest::sfmltest()
{
}

void sfmltest::run()
{
    // Main loop
    while (true) {
        sf::Joystick::update();
        if (sf::Joystick::isConnected(0)) {

            auto gamepadinfo = sf::Joystick::getIdentification(0);
//            std::cout << "name : " << gamepadinfo.name.toAnsiString() << std::endl;
//            std::cout << "productId : " << gamepadinfo.productId << std::endl;
//            std::cout << "vendorId : " << gamepadinfo.vendorId << std::endl;

            if(gamepadinfo.vendorId == 0x054c)
            {
                XINPUT_STATE state;
                ZeroMemory(&state, sizeof(XINPUT_STATE));
                unsigned short wButtons = 0;
//                for (int i = 0; i < sizeof(WORD) * 8; ++i) {
//                    int mask = 1 << i;  // 位掩码，将1左移i位
//                    if (wButtons & mask) {
//                        // 第i位为1
//                        // 在这里执行相关操作
//                    } else {
//                        // 第i位为0
//                    }
//                }
                if (sf::Joystick::isButtonPressed(0, 0)) {
                    wButtons |= 0x4000;
                }
                if (sf::Joystick::isButtonPressed(0, 1)) {
//                    std::cout << "Button 1 (cross) pressed!" << std::endl;
//                    int mask = 1 << 12;
                    wButtons = wButtons | 4096;
                }
                if (sf::Joystick::isButtonPressed(0, 2)) {
//                    std::cout << "Button 2 (circle) pressed!" << std::endl;
//                    int mask = 1 << 13;
                    wButtons = wButtons | 8192;
                }
                if (sf::Joystick::isButtonPressed(0, 3)) {
//                    std::cout << "Button 3 (Triangle) pressed!" << std::endl;
//                    int mask = 1 << 15;
                    wButtons = wButtons | 32768;
                }
                if (sf::Joystick::isButtonPressed(0, 4)) {
//                    std::cout << "Button 4 (L1) pressed!" << std::endl;
//                    int mask = 1 << 8;
                    wButtons = wButtons | 256;
                }
                if (sf::Joystick::isButtonPressed(0, 5)) {
//                    std::cout << "Button 5 (R1) pressed!" << std::endl;
//                    int mask = 1 << 9;
                    wButtons = wButtons | 512;
                }
//                if (sf::Joystick::isButtonPressed(0, 6)) {
//                    std::cout << "Button 6 (L2) pressed!" << std::endl;
//                }
//                if (sf::Joystick::isButtonPressed(0, 7)) {
//                    std::cout << "Button 7 (R2) pressed!" << std::endl;
//                }
                if (sf::Joystick::isButtonPressed(0, 8)) {
//                    std::cout << "Button 8 (share) pressed!" << std::endl;
//                    int mask = 1 << 5;
                    wButtons = wButtons | 0x20;
                }
                if (sf::Joystick::isButtonPressed(0, 9)) {
//                    std::cout << "Button 9 (menu) pressed!" << std::endl;
//                    int mask = 1 << 4;
                    wButtons = wButtons | 0x10;
                }
//                if (sf::Joystick::isButtonPressed(0, 10)) {
//                    std::cout << "Button 10 (lsb) pressed!" << std::endl;
//                }
//                if (sf::Joystick::isButtonPressed(0, 11)) {
//                    std::cout << "Button 11 (rsb) pressed!" << std::endl;
//                }
//                if (sf::Joystick::isButtonPressed(0, 12)) {
//                    std::cout << "Button 12 (PS) pressed!" << std::endl;
//                }
//                if (sf::Joystick::isButtonPressed(0, 13)) {
//                    std::cout << "Button 13 (touchpad btn) pressed!" << std::endl;
//                }

                // Check other buttons or axes as needed

                // You can also get the position of analog axes
                float xAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::X);  // ls-x
                state.Gamepad.sThumbLX = xAxis * 327.67;
                float yAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);  // ls-y
                state.Gamepad.sThumbLY = -yAxis * 327.67;
                float zAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::Z); // rs-x
                state.Gamepad.sThumbRX = zAxis * 327.67;
                float rAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::R); // rs-y
                state.Gamepad.sThumbRY = -rAxis * 327.67;
                float uAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::U); // lt
                state.Gamepad.bLeftTrigger = (uAxis+100) * 1.27;
                float vAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::V); // rt
                state.Gamepad.bRightTrigger = (vAxis+100) * 1.27;
                int pxAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX); // dirc-x
                int pyAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY); // dirc-y

                if (pxAxis < -10){
                    wButtons = wButtons | 0x04;
                }
                else if (pxAxis > 10){
                    wButtons = wButtons | 0x08;
                }

                if (pyAxis < -10) {
                    wButtons = wButtons | 0x02;
                }
                else if (pyAxis > 10) {
                    wButtons = wButtons | 0x01;
                }

                state.Gamepad.wButtons = wButtons;

                emit sig_joystickex(state);
                // Adjust the loop rate (you may need to experiment with this)
                sf::sleep(sf::milliseconds(20));
            }
            else
            {
                XINPUT_STATE state;
                ZeroMemory(&state, sizeof(XINPUT_STATE));
                XInputGetState(0, &state);
                emit sig_joystickex(state);
                sf::sleep(sf::milliseconds(10));
            }

        }
    }
}
