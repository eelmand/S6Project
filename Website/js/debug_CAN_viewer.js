// https://stackoverflow.com/questions/5835126/javascript-infinite-loop

var signals = [
    'SM_STATE', 'SM_FLOOR_REQ', 'SC_ENABLE', 
    'SC_FLOOR_CMD', 'EC_STATE', 'EC_CAR_POS',
    'F1_CALL_REQ', 'F2_CALL_REQ', 'F3_CALL_REQ', 
    'CC_FLOOR_REQ', 'CC_DOOR_STATE'
]

function updateSignal(signal) {
    document.getElementById(signal.concat('_RAW')).innerHTML = window[signal.concat('_RAW')];
    document.getElementById(signal.concat('_PHYS')).innerHTML = window[signal.concat('_PHYS')];
    document.getElementById(signal.concat('_TIMESTAMP')).innerHTML = window[signal.concat('_TIMESTAMP')];
}


function updateDB() {
    window.setInterval(function() {
        var data = JSON.parse(json_data);

        

    }, 1000);   // Repeat forever, polling every second
}

window.onload = function start(){
    updateDB();
}