// https://stackoverflow.com/questions/5835126/javascript-infinite-loop

function updateSignal(signal) {
    var raw_value = 0;
    var phys_value = ["In Transit", "Floor 1", "Floor 2", "Floor 3"];

    window.setInterval(function() {
        // Increment raw value from 0 - 3
        raw_value = (raw_value + 1) & 3;

        // Update raw value in HTML
        var raw = document.getElementById(signal.concat("_RAW"));
        raw.innerHTML = raw_value;

        // Update physical value in HTML
        var phys = document.getElementById(signal.concat("_PHYS"));
        phys.innerHTML = phys_value[raw_value];

    }, 1000);   // Repeat forever, polling every 3 seconds
}

window.onload = function start(){
    updateSignal("EC_Car_Pos");
}