#ifndef ARDUINO
#include "Arduino.hpp"
#include "ExoBuilder.hpp"
#include "BoardBuilder.hpp"
#include "Port.hpp"
#include "Linked_List.hpp"
#include "FSR.hpp"
#include "Message.hpp"

Exoskeleton* setupSystem(){
  Serial.begin(115200);
  delay(500);
  Board* board = QuadBoardDirector().build();
  Serial.println("Beginning exo building..");
  Exoskeleton* exo = QuadExoDirector().build(board);
  Serial.println("Finished exo building");
  delete board;
  return exo;
}

void testExo(){
  Exoskeleton* exo = setupSystem();
  ExoMessageBuilder builder;
  builder.
    beginLeftLegMessage()->
    beginJointMessage(0)->
    addCommand(new SetJointPid(0,0,0))->
    finishJoint()->
    finishLeg()->
    beginLeftLegMessage()->
    beginJointMessage(0)->
    addCommand(new SetJointPid(0,0,0));
  ExoMessage* msg = builder.build();
  exo->processMessage(msg);
  delete msg;
  exo->run();
  exo->sendReport();
  exo->receiveMessages();
  delete exo;
}

int main(){
  testExo();
}
#endif
