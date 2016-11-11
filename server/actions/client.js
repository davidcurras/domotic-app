var rp = require('request-promise');

var sendState = function() {
  return {
    type: 'SEND_STATE'
  }
};

var sendBusy = function() {
  return {
    type: 'SEND_BUSY'
  }
};

var sendError = function() {
  return {
    type: 'SEND_ERROR'
  }
};

module.exports = {
  sendState: sendState,
  sendBusy: sendBusy,
  sendError: sendError
};
