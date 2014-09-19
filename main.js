$(function () {
  var currentObj = null;
  var accFlag = true;
  var timeFlag = true;

  var getSeries = function(obj) {
    result = []
    if (accFlag) {
      result.push({
        name: "Acceleration",
        data: obj['ACC']
      });
    }
    if (timeFlag) {
      result.push({
        name: "Time",
        data: obj['TIME']
      });
    }
    return result;
  }

  var makeObject = function(text) {
    var rows = text.split("\n");
    for (var i in rows) {
      rows[i] = rows[i].split("\t").map(function(s) {return s.trim();});
      if (i != 0) {
        rows[i] = rows[i].map(function(s) {return Number(s);});
      }
    }
    var title = rows.shift();
    var result = {}
    for (var i in title) {
      result[title[i]] = rows.map(function(row){return row[i];});
    }
    return result;
  }

  var makeGraph = function() {
    a = $('#container').highcharts();
    if (a) a.destroy();

    if (!currentObj) return;

    $('#container').highcharts({
      title: {
        text: "Graph"
      },

      xAxis: {
        title: {
          text: "Threads"
        },
        categories: currentObj['THR']
      },

      yAxis: {
        plotLines: [{
          value: 0,
          width: 1,
          color: '#808080'
        }]
      },

      legend: {
        layout: 'vertical',
        align: 'right',
        verticalAlign: 'middle',
        borderWidth: 0
      },

      series: getSeries(currentObj)
    });
  }

  $("#input").on("paste", function(event) {
    var $el = $(this);
    setTimeout(function() {
      currentObj = makeObject($el.val());
      makeGraph();
    }, 0);
  });

  $("#accFlag").on("change", function() {
    accFlag = this.checked;
    makeGraph();
  });

  $("#timeFlag").on("change", function() {
    timeFlag = this.checked;
    makeGraph();
  });
});
