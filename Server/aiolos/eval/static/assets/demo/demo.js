 



type = ['primary', 'info', 'success', 'warning', 'danger'];

demo = {


  initDocChart: function() {
    chartColor = "#FFFFFF";

    // General configuration for the charts with Line gradientStroke
    gradientChartOptionsConfiguration = {
      maintainAspectRatio: false,
      legend: {
        display: false
      },
      tooltips: {
        bodySpacing: 4,
        mode: "nearest",
        intersect: 0,
        position: "nearest",
        xPadding: 10,
        yPadding: 10,
        caretPadding: 10
      },
      responsive: true,
      scales: {
        yAxes: [{
          display: 0,
          gridLines: 0,
          ticks: {
            display: false
          },
          gridLines: {
            zeroLineColor: "transparent",
            drawTicks: false,
            display: false,
            drawBorder: false
          }
        }],
        xAxes: [{
          display: 0,
          gridLines: 0,
          ticks: {
            display: false
          },
          gridLines: {
            zeroLineColor: "transparent",
            drawTicks: false,
            display: false,
            drawBorder: false
          }
        }]
      },
      layout: {
        padding: {
          left: 0,
          right: 0,
          top: 15,
          bottom: 15
        }
      }
    };
  },
  initDashboardPageCharts: function() {

    let sensorVals = JSON.parse(document.getElementById('sen_liste').textContent);
    console.log(sensorVals)

    let senVals1 = [[]];
    let senVals2 = [[]];
    let senVals3 = [[]];
    let senVals4 = [[]];

    let senTimes1 = [[]];
    let senTimes2 = [[]];
    let senTimes3 = [[]];
    let senTimes4 = [[]];

    lengthVals = sensorVals.length;

    console.log(lengthVals);

    for (let i = 0; i < lengthVals; i++) {

      if(sensorVals[i][0] == 7) {
        
        var sensorTimeValues = sensorVals[i].slice(3);

        console.log(sensorTimeValues);
        var lengthSensorTimeValues = sensorTimeValues.length;
        console.log(lengthSensorTimeValues);
        
        var temparray = [];
        var timetemparray = [];

        for (let j = 0; j < lengthSensorTimeValues; j++) {
          console.log(sensorTimeValues[j][0]);
          temparray.push(sensorTimeValues[j][0]);
          timetemparray.push(sensorTimeValues[j][1]);

        }
        var timeCutarray = [];
        for (let k = 0; k < lengthSensorTimeValues; k++) {
          var temp = timetemparray[k].slice(14,-5)
          timeCutarray.push(temp);
        }
        senVals1.push(temparray);
        senTimes1.push(timeCutarray);
        console.log(senVals1);
        
      }
      
      else if(sensorVals[i][0] == 1) {
        
        var sensorTimeValues = sensorVals[i].slice(3);

        console.log(sensorTimeValues);
        var lengthSensorTimeValues = sensorTimeValues.length;
        console.log(lengthSensorTimeValues);
        
        var temparray = [];
        var timetemparray = [];

        for (let j = 0; j < lengthSensorTimeValues; j++) {
          console.log(sensorTimeValues[j][0]);
          temparray.push(sensorTimeValues[j][0]);
          timetemparray.push(sensorTimeValues[j][1]);
        }
        var timeCutarray = [];
        for (let k = 0; k < lengthSensorTimeValues; k++) {
          var temp = timetemparray[k].slice(14,-5)
          timeCutarray.push(temp);
        }
        senVals2.push(temparray);
        senTimes2.push(timeCutarray);
        console.log(senVals2);

      }
      else if(sensorVals[i][0] == 2) {
        
        var sensorTimeValues = sensorVals[i].slice(3);

        console.log(sensorTimeValues);
        var lengthSensorTimeValues = sensorTimeValues.length;
        console.log(lengthSensorTimeValues);
        
        var temparray = [];
        var timetemparray = [];

        for (let j = 0; j < lengthSensorTimeValues; j++) {
          console.log(sensorTimeValues[j][0]);
          temparray.push(sensorTimeValues[j][0]);
          timetemparray.push(sensorTimeValues[j][1]);
        }
        var timeCutarray = [];
        for (let k = 0; k < lengthSensorTimeValues; k++) {
          var temp = timetemparray[k].slice(14,-5)
          timeCutarray.push(temp);
        }
        senVals3.push(temparray);
        senTimes3.push(timeCutarray);
        console.log("hierrrrrHIERIRIRRIRIRIRI");
        console.log(senVals3);
        console.log(senTimes3);
      }
      else if(sensorVals[i][0] == 3) {
        
        var sensorTimeValues = sensorVals[i].slice(3);

        console.log(sensorTimeValues);
        var lengthSensorTimeValues = sensorTimeValues.length;
        console.log(lengthSensorTimeValues);
        
        var temparray = [];
        var timetemparray = [];

        for (let j = 0; j < lengthSensorTimeValues; j++) {
          console.log(sensorTimeValues[j][0]);
          temparray.push(sensorTimeValues[j][0]);
          timetemparray.push(sensorTimeValues[j][1]);
        }
        var timeCutarray = [];
        for (let k = 0; k < lengthSensorTimeValues; k++) {
          var temp = timetemparray[k].slice(14,-5)
          timeCutarray.push(temp);
        }
        senVals4.push(temparray);
        senTimes4.push(timeCutarray);
        console.log(senVals4);

      }

    }   
    
    gradientChartOptionsConfigurationWithTooltipPurple = {
      maintainAspectRatio: false,
      legend: {
        display: false
      },

      tooltips: {
        backgroundColor: '#f5f5f5',
        titleFontColor: '#333',
        bodyFontColor: '#666',
        bodySpacing: 4,
        xPadding: 12,
        mode: "nearest",
        intersect: 0,
        position: "nearest"
      },
      responsive: true,
      scales: {
        yAxes: [{
          barPercentage: 1.6,
          gridLines: {
            drawBorder: false,
            color: 'rgba(29,140,248,0.0)',
            zeroLineColor: "transparent",
          },
          ticks: {
            suggestedMin: 60,
            suggestedMax: 125,
            padding: 20,
            fontColor: "#9a9a9a"
          }
        }],

        xAxes: [{
          barPercentage: 1.6,
          gridLines: {
            drawBorder: false,
            color: 'rgba(225,78,202,0.1)',
            zeroLineColor: "transparent",
          },
          ticks: {
            padding: 20,
            fontColor: "#9a9a9a"
          }
        }]
      }
    };

    gradientBarChartConfiguration = {
      maintainAspectRatio: false,
      legend: {
        display: false
      },

      tooltips: {
        backgroundColor: '#f5f5f5',
        titleFontColor: '#333',
        bodyFontColor: '#666',
        bodySpacing: 4,
        xPadding: 12,
        mode: "nearest",
        intersect: 0,
        position: "nearest"
      },
      responsive: true,
      scales: {
        yAxes: [{

          gridLines: {
            drawBorder: false,
            color: 'rgba(29,140,248,0.1)',
            zeroLineColor: "transparent",
          },
          ticks: {
            suggestedMin: 60,
            suggestedMax: 120,
            padding: 20,
            fontColor: "#9e9e9e"
          }
        }],
        xAxes: [{
          gridLines: {
            drawBorder: false,
            color: 'rgba(29,140,248,0.1)',
            zeroLineColor: "transparent",
          },
          ticks: {
            padding: 20,
            fontColor: "#9e9e9e"
          }
        }]
      }
    };

    var ctx = document.getElementById("chartLinePurple").getContext("2d");

    var gradientStroke = ctx.createLinearGradient(0, 230, 0, 50);

    gradientStroke.addColorStop(1, 'rgba(72,72,176,0.2)');
    gradientStroke.addColorStop(0.2, 'rgba(72,72,176,0.0)');
    gradientStroke.addColorStop(0, 'rgba(119,52,169,0)'); //purple colors

    var data = {
      labels: ['00:20', '00:25', '00:30', '00:35', '00:40', '00:45'],
      datasets: [{
        label: "Data",
        fill: true,
        backgroundColor: gradientStroke,
        borderColor: '#d048b6',
        borderWidth: 2,
        borderDash: [],
        borderDashOffset: 0.0,
        pointBackgroundColor: '#d048b6',
        pointBorderColor: 'rgba(255,255,255,0)',
        pointHoverBackgroundColor: '#d048b6',
        pointBorderWidth: 20,
        pointHoverRadius: 4,
        pointHoverBorderWidth: 15,
        pointRadius: 4,
        data: [80, 100, 70, 80, 120, 80],
      },]
    };





    var myChart = new Chart(ctx, {
      type: 'line',
      data: data,
      options: gradientChartOptionsConfigurationWithTooltipPurple
    });

    var chart_labels = senTimes1[3];
  
    

    var ctx = document.getElementById("chartBig1").getContext('2d');

    var gradientStroke = ctx.createLinearGradient(0, 230, 0, 50);

    gradientStroke.addColorStop(1, 'rgba(72,72,176,0.1)');
    gradientStroke.addColorStop(0.4, 'rgba(72,72,176,0.0)');
    gradientStroke.addColorStop(0, 'rgba(119,52,169,0)'); //purple colors
    var config = {
      type: 'line',
      data: {
        labels: chart_labels,
        datasets: [{
          label: "Sensor 1",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(53,126,216,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(53,126,216,1)',
          pointBorderColor: 'rgba(53,126,216,0)',
          pointHoverBackgroundColor: 'rgba(53,126,216,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 2,
          data: senVals1[0],
        },
        {
          label: "Sensor 2",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(245,245,245,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(245,245,245,1)',
          pointBorderColor: 'rgba(245,245,245,0)',
          pointHoverBackgroundColor: 'rgba(245,245,245,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 4,
          data: senVals1[1],
        },
        {
          label: "Sensor 3",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(113,190,198,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(113,190,198,1)',
          pointBorderColor: 'rgba(113,190,198,0)',
          pointHoverBackgroundColor: 'rgba(113,190,198,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 4,
          data: senVals1[2],
        },
        {
          label: "Sensor 4",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(10,94,134,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(10,94,134,1)',
          pointBorderColor: 'rgba(10,94,134,0)',
          pointHoverBackgroundColor: 'rgba(10,94,134,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 4,
          data: senVals1[3],
        }
      ]
      },
      options: gradientChartOptionsConfigurationWithTooltipPurple
    };
    var myChartData = new Chart(ctx, config);

    var chart_labels = senTimes2[3];
    
    var ctx = document.getElementById("chartBig2").getContext('2d');

    var gradientStroke = ctx.createLinearGradient(0, 230, 0, 50);

    gradientStroke.addColorStop(1, 'rgba(72,72,176,0.1)');
    gradientStroke.addColorStop(0.4, 'rgba(72,72,176,0.0)');
    gradientStroke.addColorStop(0, 'rgba(119,52,169,0)'); //purple colors
    var config = {
      type: 'line',
      data: {
        labels: chart_labels,
        datasets: [{
          label: "Sensor 1",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(53,126,216,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(53,126,216,1)',
          pointBorderColor: 'rgba(53,126,216,0)',
          pointHoverBackgroundColor: 'rgba(53,126,216,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 2,
          data: senVals2[0],
        },
        {
          label: "Sensor 2",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(245,245,245,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(245,245,245,1)',
          pointBorderColor: 'rgba(245,245,245,0)',
          pointHoverBackgroundColor: 'rgba(245,245,245,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 4,
          data: senVals2[1],
        },
        {
          label: "Sensor 3",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(113,190,198,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(113,190,198,1)',
          pointBorderColor: 'rgba(113,190,198,0)',
          pointHoverBackgroundColor: 'rgba(113,190,198,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 4,
          data: senVals2[2],
        },
        {
          label: "Sensor 4",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(10,94,134,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(10,94,134,1)',
          pointBorderColor: 'rgba(10,94,134,0)',
          pointHoverBackgroundColor: 'rgba(10,94,134,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 4,
          data: senVals2[3],
        }
      ]
      },
      options: gradientChartOptionsConfigurationWithTooltipPurple
    };
    var myChartData = new Chart(ctx, config);
    var ctx = document.getElementById("chartBig3").getContext('2d');







    var chart_labels = senTimes3[3];
  
    

    var ctx = document.getElementById("chartBig3").getContext('2d');

    var gradientStroke = ctx.createLinearGradient(0, 230, 0, 50);

    gradientStroke.addColorStop(1, 'rgba(72,72,176,0.1)');
    gradientStroke.addColorStop(0.4, 'rgba(72,72,176,0.0)');
    gradientStroke.addColorStop(0, 'rgba(119,52,169,0)'); //purple colors
    var config = {
      type: 'line',
      data: {
        labels: chart_labels,
        datasets: [{
          label: "Sensor 1",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(53,126,216,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(53,126,216,1)',
          pointBorderColor: 'rgba(53,126,216,0)',
          pointHoverBackgroundColor: 'rgba(53,126,216,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 2,
          data: senVals3[0],
        },
        {
          label: "Sensor 2",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(245,245,245,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(245,245,245,1)',
          pointBorderColor: 'rgba(245,245,245,0)',
          pointHoverBackgroundColor: 'rgba(245,245,245,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 4,
          data: senVals3[1],
        },
        {
          label: "Sensor 3",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(113,190,198,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(113,190,198,1)',
          pointBorderColor: 'rgba(113,190,198,0)',
          pointHoverBackgroundColor: 'rgba(113,190,198,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 4,
          data: senVals3[2],
        },
        {
          label: "Sensor 4",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: 'rgba(10,94,134,1)',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: 'rgba(10,94,134,1)',
          pointBorderColor: 'rgba(10,94,134,0)',
          pointHoverBackgroundColor: 'rgba(10,94,134,1)',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 4,
          data: senVals3[3],
        }
      ]
      },
      options: gradientChartOptionsConfigurationWithTooltipPurple
    };
    var myChartData = new Chart(ctx, config);












 
    var chart_labels = senTimes4[3];
    var ctx = document.getElementById("chartBig4").getContext('2d');

    var gradientStroke = ctx.createLinearGradient(0, 230, 0, 50);

    gradientStroke.addColorStop(1, 'rgba(72,72,176,0.1)');
    gradientStroke.addColorStop(0.4, 'rgba(72,72,176,0.0)');
    gradientStroke.addColorStop(0, 'rgba(119,52,169,0)'); //purple colors
    var config = {
      type: 'line',
      data: {
        labels: chart_labels,
        datasets: [{
          label: "My First dataset",
          fill: true,
          backgroundColor: gradientStroke,
          borderColor: '#d346b1',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          pointBackgroundColor: '#d346b1',
          pointBorderColor: 'rgba(255,255,255,0)',
          pointHoverBackgroundColor: '#d346b1',
          pointBorderWidth: 20,
          pointHoverRadius: 4,
          pointHoverBorderWidth: 15,
          pointRadius: 4,
          data: chart_data,
        }]
      },
      options: gradientChartOptionsConfigurationWithTooltipPurple
    };
    var myChartData = new Chart(ctx, config);
    $("#0").click(function() {
      var data = myChartData.config.data;
      data.datasets[0].data = chart_data;
      data.labels = chart_labels;
      myChartData.update();
    });
    $("#1").click(function() {
      var chart_data = [80, 120, 105, 110, 95, 105, 90, 100, 80, 95, 70, 120];
      var data = myChartData.config.data;
      data.datasets[0].data = chart_data;
      data.labels = chart_labels;
      myChartData.update();
    });

    var ctx = document.getElementById("CountryChart").getContext("2d");

    var gradientStroke = ctx.createLinearGradient(0, 230, 0, 50);

    gradientStroke.addColorStop(1, 'rgba(29,140,248,0.2)');
    gradientStroke.addColorStop(0.4, 'rgba(29,140,248,0.0)');
    gradientStroke.addColorStop(0, 'rgba(29,140,248,0)'); //blue colors


    var myChart = new Chart(ctx, {
      type: 'bar',
      responsive: true,
      legend: {
        display: false
      },
      data: {
        labels: ['00:20', '00:25', '00:30', '00:35', '00:40', '00:45'],
        datasets: [{
          label: "Countries",
          fill: true,
          backgroundColor: gradientStroke,
          hoverBackgroundColor: gradientStroke,
          borderColor: '#1f8ef1',
          borderWidth: 2,
          borderDash: [],
          borderDashOffset: 0.0,
          data: [53, 20, 10, 80, 100, 45],
        }]
      },
      options: gradientBarChartConfiguration
    });

  },

};