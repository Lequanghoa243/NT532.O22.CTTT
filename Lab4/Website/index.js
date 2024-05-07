const express = require('express');
const bodyParser = require('body-parser');
const { MongoClient } = require('mongodb');
const path = require('path');

const app = express();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(bodyParser.json());

// Serve static files
app.use(express.static(path.join(__dirname, 'public')));

// MongoDB Atlas connection string
const uri = "mongodb+srv://lqhoa1102:kenkaneki123@cluster0.csnu4sy.mongodb.net";

// MongoDB client
const client = new MongoClient(uri, { useNewUrlParser: true, useUnifiedTopology: true });

// Connect to MongoDB Atlas
async function connectToMongoDB() {
    try {
        await client.connect();
        console.log("Connected to MongoDB Atlas");
    } catch (error) {
        console.error("Error connecting to MongoDB Atlas:", error);
        process.exit(1);
    }
}
connectToMongoDB();

// Database name and collection name
const dbName = "Sensor";
const collectionName = "sensor";

// POST method to add device data
app.post('/sensor', async (req, res) => {
    const { deviceId, temperature, humidity, light } = req.body;
    console.log(req.body)
    if (!deviceId || !temperature || !humidity || !light) {
        return res.status(400).json({ error: 'Missing required fields' });
    }

    const timestamp = new Date(); // Get the current timestamp

    const db = client.db(dbName);
    const collection = db.collection(collectionName);

    try {
        await collection.insertOne({ deviceId, temperature, humidity, light, timestamp });
        res.status(201).json({ message: 'Device data added successfully' });
    } catch (error) {
        console.error("Error inserting device data:", error);
        res.status(500).json({ error: 'Internal server error' });
    }
});


// GET method to retrieve the latest data for device 1
app.get('/device1', async (req, res) => {
    const db = client.db(dbName);
    const collection = db.collection(collectionName);

    try {
        const device1Data = await collection.find({ deviceId: "1" }).sort({ timestamp: -1 }).limit(1).toArray();
        res.json({
            error: false,
            message: "This is a message of API",
            data:device1Data
        });
    } catch (error) {
        console.error("Error retrieving device 1 data:", error);
        res.status(500).json({ error: 'Internal server error' });
    }
});


app.get('/device2', async (req, res) => {
    const db = client.db(dbName);
    const collection = db.collection(collectionName);

    try {
        const device1Data = await collection.find({ deviceId: "2" }).sort({ timestamp: -1 }).limit(1).toArray();
        res.json({
            error: false,
            message: "This is a message of API",
            data:device1Data
        });
    } catch (error) {
        console.error("Error retrieving device 2 data:", error);
        res.status(500).json({ error: 'Internal server error' });
    }
});
app.get('/device2/light', async (req, res) => {
    const db = client.db("Sensor");
    const collection = db.collection("light");

    try {
        const device2Data = await collection.find({ deviceId: "2" }).sort({ timestamp: -1 }).limit(1).toArray();
        const latestLightStatus = device2Data.length > 0 ? device2Data[0].light : 'unknown';
        res.status(200).json({ status: latestLightStatus });
    } catch (error) {
        console.error("Error retrieving device 2 light status:", error);
        res.status(500).json({ error: 'Internal server error' });
    }
});

// POST method to update the light status for device 2
app.post('/device2/light', async (req, res) => {
    const { status } = req.body;
    
    // Validate the status
    if (status !== 'on' && status !== 'off') {
        return res.status(400).json({ error: 'Invalid status value' });
    }

    const timestamp = new Date(); // Get the current timestamp

    const db = client.db("Sensor");
    const collection = db.collection("light");

    try {
        await collection.insertOne({ deviceId: "2", light: status, timestamp });
        res.status(200).json({ message: `Light status updated to ${status} for device 2` });
    } catch (error) {
        console.error("Error updating device 2 light status:", error);
        res.status(500).json({ error: 'Internal server error' });
    }
});

// Start the server
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});
