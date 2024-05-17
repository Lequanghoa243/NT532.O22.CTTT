const mongoose = require("mongoose");

var sensorSchema = new mongoose.Schema(
  {
    light: {
      type: Number,

    },
    humidity: {
      type: Number,

    },
    temperature: {
      type: Number,

    },
    device: {
      type: String,

    }
  },
  {
    timestamps: true,
  }
);

module.exports = mongoose.model("sensor", sensorSchema);
