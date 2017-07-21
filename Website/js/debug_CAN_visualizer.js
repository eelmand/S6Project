// https://stackoverflow.com/questions/5835126/javascript-infinite-loop



var EC_CAR_POS = 0;
var EC_ENABLE = 0;
var CC_DOOR_STATE = 0;
var F1_CALL_REQ = 0;
var F2_CALL_REQ = 0;
var F3_CALL_REQ = 0;
var SM_STATE = "Car Not Moving";
var SM_FLOOR_REQ = "No Request";


var json_data = {};


// Function to request that the server run debug_CAN_viewer.php again
function updateData() {
    // Get most recent data from database
    console.log('here');
    $.ajax({
        url: 'http://adequateelevators.com/Website/php/debug_CAN_viewer.php',
        dataType: 'json',
        success: function(data) {
            json_data = data;
            console.log(json_data);
        }
    });

    console.log('here');

    // Process that data
    EC_CAR_POS = json_data['EC_CAR_POS_RAW'];
    EC_ENABLE = json_data['EC_ENABLE_RAW'];
    CC_DOOR_STATE = json_data['CC_DOOR_STATE_RAW'];
    F1_CALL_REQ = json_data['F1_CALL_REQ_RAW'];
    F2_CALL_REQ = json_data['F2_CALL_REQ_RAW'];
    F3_CALL_REQ = json_data['F3_CALL_REQ_RAW'];
    SM_STATE = json_data['SM_STATE_PHYS'];
    SM_FLOOR_REQ = json_data['SM_FLOOR_REQ_PHYS'];
}

// Function that actually updates the visualizer data
function updateVisualizer() {
    // Update floor numbers
    switch(EC_CAR_POS) {
        case '0':
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
        case '1':
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
        case '2':
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
        case '3':
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
        case '0':
            document.getElementById("EC_ENABLE").style.backgroundColor = "white";
            break;
        case '1':
            document.getElementById("EC_ENABLE").style.backgroundColor = "green";
            break;
    }

    // Update CC Door Open LED
    switch(CC_DOOR_STATE) {
        case '0':
            document.getElementById("CC_DOOR_STATE").style.backgroundColor = "white";
            break;
        case '1':
            document.getElementById("CC_DOOR_STATE").style.backgroundColor = "green";
            break;
    }

    // Update Floor Call Request LEDs
    switch(F1_CALL_REQ) {
        case '0':
            document.getElementById("F1_CALL_REQ").style.backgroundColor = "white";
            break;
        case '1':
            document.getElementById("F1_CALL_REQ").style.backgroundColor = "green";
            break;
    }        
    switch(F2_CALL_REQ) {
        case '0':
            document.getElementById("F2_CALL_REQ").style.backgroundColor = "white";
            break;
        case '1':
            document.getElementById("F2_CALL_REQ").style.backgroundColor = "green";
            break;
    }        
    switch(F3_CALL_REQ) {
        case '0':
            document.getElementById("F3_CALL_REQ").style.backgroundColor = "white";
            break;
        case '1':
            document.getElementById("F3_CALL_REQ").style.backgroundColor = "green";
            break;
    }        

    // Update State Machine Info
    document.getElementById("SM_STATE").innerHTML = SM_STATE;
    document.getElementById("SM_FLOOR_REQ").innerHTML = SM_FLOOR_REQ;
}


// Main loop, calls other functions once a second
function main() {
    window.setInterval(function() {
        updateData();
        updateVisualizer();
    }, 1000);   // Repeat forever, polling every second
}


// On load, start main loop
window.onload = function start(){
    main();
}