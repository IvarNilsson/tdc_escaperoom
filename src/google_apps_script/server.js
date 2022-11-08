var ss = SpreadsheetApp.openById('*****');
var sheet = ss.getSheetByName('Blad1');

function doGet(e) {
  Logger.log(JSON.stringify(e));
  if (e.parameter == undefined) {
    return ContentService.createTextOutput("undefined1");
  } else if (e.parameter.read !== undefined) {
    return ContentService.createTextOutput(sheet.getRange(e.parameter.read).getValue());

  } else if (e.parameter.B2 !== undefined) {
    sheet.getRange("B2").setValue(e.parameter.B2);
    return ContentService.createTextOutput("B2 updated (" + e.parameter.B2 + ").");
  } else if (e.parameter.C2 !== undefined) {
    sheet.getRange("C2").setValue(e.parameter.C2);
    return ContentService.createTextOutput("C2 updated (" + e.parameter.C2 + ").");


  } else if (e.parameter.F2 !== undefined) {
    sheet.getRange("F2").setValue(e.parameter.F2);
    return ContentService.createTextOutput("F2 updated (" + e.parameter.F2 + ").");
  } else if (e.parameter.F3 !== undefined) {
    sheet.getRange("F3").setValue(e.parameter.F3);
    return ContentService.createTextOutput("F3 updated (" + e.parameter.F3 + ").");

  } else if (e.parameter.G2 !== undefined) {
    sheet.getRange("G2").setValue(e.parameter.G2);
    return ContentService.createTextOutput("G2 updated (" + e.parameter.G2 + ").");
  } else if (e.parameter.G3 !== undefined) {
    sheet.getRange("G3").setValue(e.parameter.G3);
    return ContentService.createTextOutput("G3 updated (" + e.parameter.G3 + ").");

  } else if (e.parameter.H2 !== undefined) {
    sheet.getRange("H2").setValue(e.parameter.H2);
    return ContentService.createTextOutput("H2 updated (" + e.parameter.H2 + ").");
  } else if (e.parameter.H3 !== undefined) {
    sheet.getRange("H3").setValue(e.parameter.H3);
    return ContentService.createTextOutput("H3 updated (" + e.parameter.H3 + ").");

  } else if (e.parameter.I2 !== undefined) {
    sheet.getRange("I2").setValue(e.parameter.I2);
    return ContentService.createTextOutput("I2 updated (" + e.parameter.I2 + ").");
  } else if (e.parameter.I3 !== undefined) {
    sheet.getRange("I3").setValue(e.parameter.I3);
    return ContentService.createTextOutput("I3 updated (" + e.parameter.I3 + ").");

  } else if (e.parameter.J2 !== undefined) {
    sheet.getRange("J2").setValue(e.parameter.J2);
    return ContentService.createTextOutput("J2 updated (" + e.parameter.J2 + ").");
  } else if (e.parameter.J3 !== undefined) {
    sheet.getRange("J3").setValue(e.parameter.J3);
    return ContentService.createTextOutput("J3 updated (" + e.parameter.J3 + ").");



  } else if (e.parameter.write == undefined) {
    return ContentService.createTextOutput("undefined2");
  } else if (e.parameter.read == undefined) {
    return ContentService.createTextOutput("undefined3");
  }
  return ContentService.createTextOutput("empty");
  //----------------------------------------------------------------------------------
}

//Extra Function. Not used in this project.
//planning to use in future projects.
//this function is used to handle POST request
function doPost(e) {
  var val = e.parameter.value;

  if (e.parameter.value !== undefined) {
    var range = sheet.getRange('A1');
    range.setValue(val);
  }
}