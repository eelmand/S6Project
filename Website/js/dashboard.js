/*  Description: Javascript for the dashboard.html page
	Author: David Eelman 
	Date: June 30, 2017
*/


var gFloorNumberReq = 0;
// Call a php script to write into the database the floor requested by the user
function callElevator(floorNumber){
	$.ajax({
		type: 'POST',
		url: './php/dashboard_insert.php',
		data: { floorRequested : floorNumber },
		success: function(result) {
			if(result){
				gFloorNumberReq = floorNumber;
				if(floorNumber){
					document.getElementById(floorNumber).classList.add('btn-info');
					if(floorNumber != 1){
						document.getElementById(1).classList.remove('btn-info');
					}
					if(floorNumber != 2){
						document.getElementById(2).classList.remove('btn-info');
					}
					if(floorNumber != 3){
						document.getElementById(3).classList.remove('btn-info');
					}
				}
			}
		}
	});
}

var json_data_pos = {};
var lastValue = 0;
// Function to get the latest physical elevator position and update the on screen elevator
function updatePosition(){
	if(json_data_pos['EC_CAR_POS_RAW'] != 0){
		if(json_data_pos['EC_CAR_POS_RAW'] == gFloorNumberReq){
			document.getElementById(gFloorNumberReq).classList.remove('btn-info');
			callElevator(0);
		}
		if(json_data_pos['EC_CAR_POS_RAW'] != lastValue){
			if(json_data_pos['EC_CAR_POS_RAW'] == 1){
				$("#elevator-picture").animate({marginTop:200}, 1000, function() {
					$("#floor-display").sevenSeg({ value: 1 });
					lastValue = 1;
			});
			}
			else if(json_data_pos['EC_CAR_POS_RAW'] == 2){
				$("#elevator-picture").animate({marginTop:100}, 1000, function() {
					$("#floor-display").sevenSeg({ value: 2 });
					lastValue = 2;
				});
			}
			else if(json_data_pos['EC_CAR_POS_RAW'] == 3){
				$("#elevator-picture").animate({marginTop : 0}, 1000, function() {
					$("#floor-display").sevenSeg({ value: 3 });
					lastValue = 3;
				});
			}
			else{}
		}
	}
}

var json_data_stats = {};
var stats = ['FLRS_TRVL_DAY', 'FLRS_TRVL_WEEK', 'MOST_VSTD_FLR'];

function updateStats(stats){
	document.getElementById(stats.concat('_VALUE')).innerHTML = json_data_stats[stats.concat('_VALUE')];
    document.getElementById(stats.concat('_TIMESTAMP')).innerHTML = json_data_stats[stats.concat('_TIMESTAMP')];
}

// Function to request that the server run dashboard.php every second in the background
function updateData() {
	window.setInterval(function() {
		$.ajax({
			url: './php/dashboard.php',
			dataType: 'json',
			success: function(data_pos) {
				json_data_pos = data_pos;
				console.log(json_data_pos);
				updatePosition();
			}
		});
		$.ajax({
			url: './php/dashboard_stats.php',
			dataType: 'json',
			success: function(data_stats) {
				json_data_stats = data_stats;
				console.log(json_data_stats);
				stats.forEach(updateStats);
			}
		});
	}, 1000);   // Repeat forever, polling every second
}

// Kick off the update data function when the page loads
window.onload = function start(){
	updateData();
}

/*
// Beautiful chart that maybe I'll use one day
Chart.defaults.global.defaultFontColor = 'white';
var ctx = document.getElementById("myChart").getContext('2d');
var myChart = new Chart(ctx, {
	type: 'bar',
	data: {
		labels: ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"],
		datasets: [{
			data: [12, 19, 3, 5, 2, 3, 8],
			backgroundColor: [
				'rgba(255, 99, 132, 0.2)',
				'rgba(54, 162, 235, 0.2)',
				'rgba(255, 206, 86, 0.2)',
				'rgba(75, 192, 192, 0.2)',
				'rgba(153, 102, 255, 0.2)',
				'rgba(255, 159, 64, 0.2)',
				'rgba(150, 250, 5, 0.2)'
			],
			borderColor: [
				'rgba(255,99,132,1)',
				'rgba(54, 162, 235, 1)',
				'rgba(255, 206, 86, 1)',
				'rgba(75, 192, 192, 1)',
				'rgba(153, 102, 255, 1)',
				'rgba(255, 159, 64, 1)',
				'rgba(150, 250, 5, 1)'
			],
			borderWidth: 1
		}]
	},
	options: {
		maintainAspectRatio: false,
		title: {
			display: true,
			text: 'Elevator Floors Travelled by Day',
			fontSize: 18
		},
		legend: {
			display: false
		},
		scales: {
			yAxes: [{
				scaleLabel: {
					display: true,
					labelString: 'Floors Travelled'
				},
				gridLines:{
					color:"rgba(255,255,255,0.5)",
					zeroLineColor:"rgba(255,255,255,0.5)"
				},
				ticks: {
					beginAtZero:true
				}
			}],
			xAxes: [{
				scaleLabel: {
					display: true,
					labelString: 'Days'
				},
			}]
		}
	}
});*/