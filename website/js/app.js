$(document).ready(function(){
	$.ajax({
		url: "http://www.plantproject.dx.am/data.php",
		method: "GET",
		success: function(data) {
			console.log(data);
			var time = [];
			var temp = [];

			for(var i in data) {
				time.push(data[i].measurement_time_server);
				temp.push(data[i].measurement_value);
			}

			var chartdata = {
				labels: time,
				datasets : [
					{
						label: 'Temperature',
						backgroundColor: 'rgba(200, 200, 200, 0.75)',
						borderColor: 'rgba(200, 200, 200, 0.75)',
						hoverBackgroundColor: 'rgba(200, 200, 200, 1)',
						hoverBorderColor: 'rgba(200, 200, 200, 1)',
                                                fill: false,
						data: temp
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
                                        }
                                }
			});
		},
		error: function(data) {
			console.log(data);
		}
	});
});