/* Plot CAN elevator statistics charts */
/* Used open-source JS library: Charts.js
http://www.chartjs.org/docs/latest/getting-started/usage.html
*/


// Shows total distance travelled by elevator in floors monthly
var ctx = document.getElementById("chart_total_floors").getContext('2d');

var total_floors = new Chart(ctx, {
    type: 'bar',
    data: {
        labels: ["May", "June", "July", "August"],
        datasets: [{
            label: 'Floors travelled',
            data: [7, 12, 19, 3],
            backgroundColor: [
				'rgba(255, 99, 132, 0.2)',
                'rgba(54, 162, 235, 0.2)',
                'rgba(255, 206, 86, 0.2)',
                'rgba(75, 192, 192, 0.2)',
            ],
            borderColor: [
                'rgba(255,99,132,1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
                'rgba(75, 192, 192, 1)',
            ],
            borderWidth: 1
        }]
    },
    options: {
        title:{
            display:true,
            text:'Monthly distance travelled'
        }
        /*scales: {
		    xAxes: [{
		        display: true,
		        scaleLabel: {
		            display: true,
		            labelString: 'Month'
		        }
		    }],
		    yAxes: [{
		        ticks: {
                    beginAtZero:true
                }
		        display: true,
		        scaleLabel: {
		            display: true,
		            labelString: 'Floors'
		        }
		    }]
		}*/
    }
});


// Shows total distance travelled by elevator in floors daily (last week)
ctx = document.getElementById("char_week_floors").getContext('2d');

var week_floors = new Chart(ctx, {
    type: 'line',
    data: {
        labels: ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"],
        datasets: [{
            label: 'Floors travelled',
            data: [1, 3, 6, 1, 0, 8, 4],
            backgroundColor: 'red',
            borderColor: 'red',
            fill: false
        }]
    }
    /*options: {
        responsive: true,
        title:{
            display:true,
            text:'Daily distance travelled'
        },
        scales: {
		    xAxes: [{
		        display: true,
		        scaleLabel: {
		            display: true,
		            labelString: 'Day'
		        }
		    }],
		    yAxes: [{
		        display: true,
		        scaleLabel: {
		            display: true,
		            labelString: 'Floors'
		        }
		    }]
		}
    }*/
});


/*
// Shows total distance travelled by elevator in floors daily (last week)
ctx = document.getElementById("chart_popular_floor").getContext('2d');

*/