#ifndef CONSTS_HPP
#define CONSTS_HPP

const int TAILLEGRILLE = 50;
const float PHERO_NID_NEAR_NID = 1.0f - (1.0f/TAILLEGRILLE);

const int AMOUNT_OF_SUGAR_TO_SET = 60;
const int AMOUT_OF_SUGAR_TO_REMOVE = 10;
const int AMOUNT_OF_SUGAR_FOURMI_PORTE = AMOUT_OF_SUGAR_TO_REMOVE;

const float MAX_PHERO_SUGAR_INTENSITY = 255;
const float AMOUT_OF_PHERO_SUGAR_TO_REMOVE = 5;

const int AMOUNT_OF_INIT_RAND_SUGAR = 4;

const int NUMBER_OF_CASTES = 3;

const int WINDOW_SIZE = 1024;
const int grid_size = TAILLEGRILLE;
const float scale = WINDOW_SIZE / (TAILLEGRILLE);
const int INITIAL_GAME_SPEED = 20;
const int GAME_SPEED_CHANGE = 5;
const int NEW_SUGAR_APP_SPEED = 50;

const bool INIT_SHOW_PHERO_NID = true;
// const int NEW_SUGAR_APP_SPEED = 5;

const int AMOUT_OF_SUGAR_FOR_NEW_FOURMI = AMOUNT_OF_SUGAR_TO_SET;
const int MAX_NUMBER_OF_FOURMI_IN_COLONY = 50;
// const int MAX_NUMBER_OF_FOURMI_IN_COLONY = 5000;



#endif