$(document).ready(function(){
	$.ajax({
		url: "data.php",
		method: "GET",
		success: function(data) {
			console.log(data);

			var temperature = [];

			for(var i in data) {
				temperature.push({x:new Date(data[i].measurement_time_server), y:data[i].measurement_value});
			}

			var chartdata = {
				//labels: time,
				datasets : [
					{
						label: 'Temperature',
						backgroundColor: 'rgba(200, 200, 200, 0.75)',
						borderColor: 'rgba(200, 200, 200, 0.75)',
						hoverBackgroundColor: 'rgba(200, 200, 200, 1)',
						hoverBorderColor: 'rgba(200, 200, 200, 1)',
						fill: false,
						data: temperature
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
								display: true,
								labelString: 'Date'
							},
							ticks: {
								major: {
									fontStyle: 'bold',
									fontColor: '#FF0000'
								}
							}
						}],
						yAxes: [{
							display: true,
							scaleLabel: {
								display: true,
								labelString: 'value'
							}
						}]
					}
				}
			});
		},
		error: function(data) {
			console.log(data);
		}
	});
});




