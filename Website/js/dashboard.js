function floor_3(){
	$("#elevator-picture").animate({marginTop : 0}, 1500, function() {
		$("#floor-display").sevenSeg({ value: 3 });
		//document.getElementById("elevatorPic").src="images/doors_closed.jpg";
	});
}

function floor_2(){
	$("#elevator-picture").animate({marginTop:100}, 1500, function() {
		$("#floor-display").sevenSeg({ value: 2 });
	});
}

function floor_1(){
	$("#elevator-picture").animate({marginTop:200}, 1500, function() {
		$("#floor-display").sevenSeg({ value: 1 });
	});
}


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
});
