from dbClass import *
# read---------------------------------------------------------

@app.route('/')
def index():

    return render_template('index.html')


@app.route('/tabel')
def tabel():

    return render_template('tabel.html')

# create-------------------------------------------------------

# link untuk input data
# localhost:5001/inputData?mode=save&temperature=30&humidity=79&moisture=50&co=0.5&count_tip=1

@app.route('/inputData', methods=['GET'])
def inputData():
    dateToday = date.today()
    HutanDataToday = Hutan.query.filter(Hutan.timestamp >= dateToday).filter(Hutan.timestamp < dateToday + timedelta(days=1)).all()
    countTipDataToday = sum([data.count_tip for data in HutanDataToday])

    try:
        mode = request.args.get('mode')
        if mode != 'save':
            return jsonify({"error": "Mode not found."}), 400

        else:
            temperature = request.args.get('temperature', type=float)
            humidity = request.args.get('humidity', type=float)
            moisture = request.args.get('moisture', type=float)
            co = request.args.get('co', type=float)
            count_tip = request.args.get('count_tip', type=int)

            if temperature is None or humidity is None or moisture is None or co is None or count_tip is None:
                return jsonify({"error": "Bad request."}), 400
            
            countTipDataAverageToday = countTipDataToday + count_tip

            if countTipDataAverageToday == 0:
                rainfall = 0
            
            rainfall = 0.33 * countTipDataAverageToday

            # upload data to database

            newSPDKHData = Hutan(
                temperature=temperature,
                humidity=humidity,
                moisture=moisture,
                co=co,
                count_tip=count_tip,
                rainfall=rainfall
            )

            db.session.add(newSPDKHData)

            db.session.commit()

            return redirect(url_for('lihatData'))

    except Exception as e:
        return jsonify({"error": "An error occurred while trying to add sensor data."}), 500


@app.route('/lihatData', methods=['GET'])
def lihatData():
    # tampilkan seluruh database dalam format json
    
    hutanDatas = Hutan.query.all()
    data = []
    for item in hutanDatas:
        data.append({
            "id": item.id,
            "temperature": item.temperature,
            "humidity": item.humidity,
            "moisture": item.moisture,
            "co": item.co,
            "rainfall": item.rainfall,
            "timestamp": item.timestamp
        })

    response = {
        "status": "success",
        "message": "Sensor data added successfully!",
        "data": data
    }

    return jsonify(response), 200


if __name__ == '__main__':
    # Launch the application
    app.run(port = 5001, debug=True)
