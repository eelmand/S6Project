// https://stackoverflow.com/questions/5835126/javascript-infinite-loop

var EC_CAR_POS = 0;
var EC_ENABLE = 0;
var CC_DOOR_STATE = 0;
var F1_CALL_REQ = 0;
var F2_CALL_REQ = 0;
var F3_CALL_REQ = 0;
var SM_STATE = 0;
var SM_FLOOR_REQ = 0;
var SM_STATE_PHYS = ["CAR NOT MOVING", "REQ NEW FLOOR", "CAR MOVING"];
var SM_FLOOR_REQ_PHYS = ["No Request", "Req Floor 1", "Req Floor 2", "Req Floor 3"];

function updateVisualizer() {
    window.setInterval(function() {
        // Increment raw values
        EC_CAR_POS = (EC_CAR_POS + 1) & 3;
        EC_ENABLE = (EC_ENABLE + 1) & 1;
        CC_DOOR_STATE = (CC_DOOR_STATE + 1) & 1;
        F1_CALL_REQ = (F1_CALL_REQ + 1) & 1;
        F2_CALL_REQ = (F2_CALL_REQ + 1) & 1;
        F3_CALL_REQ = (F3_CALL_REQ + 1) & 1;
        SM_STATE = (SM_STATE + 1) & 3;
        SM_FLOOR_REQ = (SM_FLOOR_REQ + 1) & 3;

        // Update floor numbers
        switch(EC_CAR_POS) {
            case 0:
                elements = document.getElementsByClassName("F3");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "white";
                }
                elements = document.getElementsByClassName("F2");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "white"; }
                elements = document.getElementsByClassName("F1");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "white";
                }
                break;
            case 1:
                elements = document.getElementsByClassName("F3");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "white";
                }
                elements = document.getElementsByClassName("F2");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "white";
                }
                elements = document.getElementsByClassName("F1");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "green";
                }
                break;
            case 2:
                elements = document.getElementsByClassName("F3");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "white";
                }
                elements = document.getElementsByClassName("F2");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "green";
                }
                elements = document.getElementsByClassName("F1");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "white";
                }
                break;
            case 3:
                elements = document.getElementsByClassName("F3");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "green";
                }
                elements = document.getElementsByClassName("F2");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "white";
                }
                elements = document.getElementsByClassName("F1");
                for(var i=0; i<elements.length; i++) {
                    elements[i].style.backgroundColor = "white";
                }
                break;                
        }

        // Update EC Enable LED
        switch(EC_ENABLE) {
            case 0:
                document.getElementById("EC_ENABLE").style.backgroundColor = "white";
                break;
            case 1:
                document.getElementById("EC_ENABLE").style.backgroundColor = "green";
                break;
        }

        // Update CC Door Open LED
        switch(CC_DOOR_STATE) {
            case 0:
                document.getElementById("CC_DOOR_STATE").style.backgroundColor = "white";
                break;
            case 1:
                document.getElementById("CC_DOOR_STATE").style.backgroundColor = "green";
                break;
        }

        // Update Floor Call Request LEDs
        switch(F1_CALL_REQ) {
            case 0:
                document.getElementById("F1_CALL_REQ").style.backgroundColor = "white";
                break;
            case 1:
                document.getElementById("F1_CALL_REQ").style.backgroundColor = "green";
                break;
        }        
        switch(F2_CALL_REQ) {
            case 0:
                document.getElementById("F2_CALL_REQ").style.backgroundColor = "white";
                break;
            case 1:
                document.getElementById("F2_CALL_REQ").style.backgroundColor = "green";
                break;
        }        
        switch(F3_CALL_REQ) {
            case 0:
                document.getElementById("F3_CALL_REQ").style.backgroundColor = "white";
                break;
            case 1:
                document.getElementById("F3_CALL_REQ").style.backgroundColor = "green";
                break;
        }        

        // Update State Machine Info
        document.getElementById("SM_STATE").innerHTML = SM_STATE_PHYS[SM_STATE];
        document.getElementById("SM_FLOOR_REQ").innerHTML = SM_FLOOR_REQ_PHYS[SM_FLOOR_REQ];


    }, 1000);   // Repeat forever, polling every 1 seconds
}

window.onload = function start(){
    updateVisualizer();
}