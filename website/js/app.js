$(document).ready(function(){
	$.ajax({
		url: "data.php",
		method: "GET",
		success: function(data) {
			console.log(data);

			var temperature = [];
			var humidity = [];

			for(var i in data) {
				if(data[i].measurement_type == 1)
					temperature.push({x:new Date(data[i].measurement_time_server), y:data[i].measurement_value});
				else if(data[i].measurement_type == 2)
					humidity.push({x:new Date(data[i].measurement_time_server), y:data[i].measurement_value});
			}

			var chartdata = {
				datasets : [
					{
						label: 'Temperature',
						yAxisID: 'T',
						backgroundColor: 'rgba(255, 50, 50, 0.75)',
						borderColor: 'rgba(255, 50, 50, 0.75)',
						hoverBackgroundColor: 'rgba(255, 50, 50, 1)',
						hoverBorderColor: 'rgba(255, 50, 50, 1)',
						fill: false,
						data: temperature
					},
					{
						label: 'Humidity',
						yAxisID: 'H',
						backgroundColor: 'rgba(50, 50, 255, 0.75)',
						borderColor: 'rgba(50, 50, 255, 0.75)',
						hoverBackgroundColor: 'rgba(50, 50, 255, 1)',
						hoverBorderColor: 'rgba(50, 50, 255, 1)',
						fill: false,
						data: humidity
					}
				]
			};

			var ctx = $("#mycanvas");

			var barGraph = new Chart(ctx, {
				type: 'line',
				data: chartdata,
				options: {
					responsive: true,
					title: {
						display: true,
						text: 'Environmental'
					},					
					scales: {
						xAxes: [{
							type: 'time',
							display: true,
							scaleLabel: {
								display: false,
								labelString: 'Date'
							},
						}],
						yAxes: [{
							id: 'T',
							position: 'left',
							display: true,
							scaleLabel: {
								display: true,
								labelString: 'Temperature',
								fontColor: 'rgba(255, 50, 50, 1)',
								fontStyle: 'bold',
							}
						},{
							id: 'H',
							position: 'right',
							display: true,
							scaleLabel: {
								display: true,
								labelString: 'Humidity',
								fontColor: 'rgba(50, 50, 255, 1)',
								fontStyle: 'bold',
							}
						}]
					},
					legend: {
						display: false
					}
				}
			});
		},
		error: function(data) {
			console.log(data);
		}
	});
});




