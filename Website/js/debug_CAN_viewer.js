// https://stackoverflow.com/questions/5835126/javascript-infinite-loop

var json_data = {};

var signals = [
    'SM_STATE', 'SM_FLOOR_REQ', 'SC_ENABLE', 
    'SC_FLOOR_CMD', 'EC_STATE', 'EC_CAR_POS',
    'F1_CALL_REQ', 'F2_CALL_REQ', 'F3_CALL_REQ', 
    'CC_FLOOR_REQ', 'CC_DOOR_STATE'
]


// Function that actually prints the signal values in the table
function updateSignal(signal) {
    document.getElementById(signal.concat('_RAW')).innerHTML = json_data[signal.concat('_RAW')];
    document.getElementById(signal.concat('_PHYS')).innerHTML = json_data[signal.concat('_PHYS')];
    document.getElementById(signal.concat('_TIMESTAMP')).innerHTML = json_data[signal.concat('_TIMESTAMP')];
}

// Function to request that the server run debug_CAN_viewer.php again
function updateData() {
    window.setInterval(function() {
        $.ajax({
            url: './php/debug_CAN_viewer.php',
            dataType: 'json',
            success: function(data) {
                json_data = data;
                console.log(json_data);
                signals.forEach(updateSignal);
            }
        });
    }, 1000);   // Repeat forever, polling every second
}

window.onload = function start(){
    updateData();
}