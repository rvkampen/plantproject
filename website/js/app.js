function getUrlVars() {
	var vars = {};
	var parts = window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi, function(m,key,value) {
		vars[key] = value;
	});
	return vars;
}
function getVar(q) {
	var v = getUrlVars();
	if(v[q])
		return v[q];
	return "";
}

function processData(data, canvas) {
    var sets = [];

    for (var set in data) {
        var measurements = [];
        for (var i in data[set]["data"]) {
            measurements.push({ x: new Date(data[set]["data"][i].time), y: String(data[set]["data"][i].value) });
        }

        var r = data[set]["type"][0] == "T" ? 255 : 50 * data[set]["sensor_id"];
        var g = data[set]["type"][0] == "P" ? 255 : 50 * data[set]["sensor_id"];
        var b = data[set]["type"][0] == "H" ? 255 : 50 * data[set]["sensor_id"];

        var color = String(r) + ", " + String(g) + ", " + String(b);

        sets.push({
            label: data[set]["name"],
            yAxisID: data[set]["type"][0],
            backgroundColor: 'rgba(' + color + ', 0.75)',
            borderColor: 'rgba(' + color + ', 0.75)',
            hoverBackgroundColor: 'rgba(' + color + ', 1)',
            hoverBorderColor: 'rgba(' + color + ', 1)',
            fill: false,
            data: measurements
        });
    }

    var chartdata = {
        datasets: sets
    };

    var graph = new Chart(canvas, {
        type: 'line',
        data: chartdata,
        options: {
            responsive: true,
            animation: false,
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
                yAxes: [
                    {
                        id: 'T',
                        position: 'left',
                        display: true,
                        scaleLabel: {
                            display: true,
                            labelString: 'Temperature',
                            fontColor: 'rgba(255, 50, 50, 1)',
                            fontStyle: 'bold',
                        }
                    },
                    {
                        id: 'H',
                        position: 'right',
                        display: true,
                        scaleLabel: {
                            display: true,
                            labelString: 'Humidity',
                            fontColor: 'rgba(50, 50, 255, 1)',
                            fontStyle: 'bold',
                        }
                    },
                    {
                        id: 'P',
                        position: 'right',
                        display: true,
                        scaleLabel: {
                            display: true,
                            labelString: 'Pressure',
                            fontColor: 'rgba(50, 255, 50, 1)',
                            fontStyle: 'bold',
                        }
                    }]
            }
            //,
            //legend: {
            //	display: false
            //}
        }
    });

}
 
$(document).ready(function(){
	$.ajax({
		url: "data.php?timespan="+getVar('timespan'),
		method: "GET",
        success: function (data) {
            processData(data, $("#mycanvas"));
		},
		error: function(data) {
			console.log(data);
		}
	});
});
