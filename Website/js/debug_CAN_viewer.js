// https://stackoverflow.com/questions/5835126/javascript-infinite-loop

var raw_values = {
    SM_STATE:0,
    SM_FLOOR_REQ:0,
    SC_ENABLE:0,
    SC_FLOOR_CMD:0,
    EC_STATE:0,
    EC_CAR_POS:0,
    F1_CALL_REQ:0,
    F2_CALL_REQ:0,
    F3_CALL_REQ:0,
    CC_FLOOR_REQ:0,
    CC_DOOR_STATE:0
}

var phys_values = {
    SM_STATE:["CAR NOT MOVING", "REQUEST NEW FLOOR", "CAR MOVING"],
    SM_FLOOR_REQ:["No Request", "Req Floor 1", "Req Floor 2", "Req Floor 3"],
    SC_ENABLE:["Cmd Disable Elevator", "Cmd Enable Elevator"],
    SC_FLOOR_CMD:["Cmd Don't Care", "Cmd Floor 1", "Cmd Floor 2", "Cmd Floor 3"],
    EC_STATE:["Elevator Disabled", "Elevator Enabled"],
    EC_CAR_POS:["In Transit", "Floor 1", "Floor 2", "Floor 3"],
    F1_CALL_REQ:["No Request", "Car Requested"],
    F2_CALL_REQ:["No Request", "Car Requested"],
    F3_CALL_REQ:["No Request", "Car Requested"],
    CC_FLOOR_REQ:["No Request", "Req Floor 1", "Req Floor 2", "Req Floor 3"],
    CC_DOOR_STATE:["Door Open", "Door Closed"]   
}


function updateSignal(signal) {
    window.setInterval(function() {
        // Increment raw value from 0 - 3
        raw_values[signal] = (raw_values[signal] + 1) & 3;

        // Update raw value in HTML
        var raw = document.getElementById(signal.concat("_RAW"));
        raw.innerHTML = raw_values[signal];

        // Update physical value in HTML
        var phys = document.getElementById(signal.concat("_PHYS"));
        var values = phys_values[signal];
        raw = raw_values[signal];
        phys.innerHTML = values[raw];

    }, 1000);   // Repeat forever, polling every 3 seconds
}

window.onload = function start(){
    updateSignal("SM_STATE");
    updateSignal("SM_FLOOR_REQ");
    updateSignal("SC_ENABLE");
    updateSignal("SC_FLOOR_CMD");
    updateSignal("EC_STATE");
    updateSignal("EC_CAR_POS");
    updateSignal("F1_CALL_REQ");
    updateSignal("F2_CALL_REQ");
    updateSignal("F3_CALL_REQ");
    updateSignal("CC_FLOOR_REQ");
    updateSignal("CC_DOOR_STATE");
}