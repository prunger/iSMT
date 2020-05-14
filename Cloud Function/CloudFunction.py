#
#
# main() will be run when you invoke this action
#
# @param Cloud Functions actions accept a single parameter, which must be a JSON object.
#
# @return The output of this action, which must be a JSON object.
#
#

import cloudant
import ibm_db


def main(payload):
    api_key = 'ciestruitypherrdrictions'
    password = '263df89e714a16041272a7b85b45a1206d8c29d6'
    account = 'cef81edb-8e36-4aa5-a9e5-9c0c606b1483-bluemix'

    dbu = ibm_db.connect("DATABASE=BLUDB;HOSTNAME=dashdb-txn-flex-yp-dal09-172.services.dal.bluemix.net;PORT=50000;PROTOCOL=TCPIP;UID=bluadmin;PWD=Njc5YmYxZTRlZGM4;", "", "")
    

    #Connection Test - Sample
    client = cloudant.Cloudant(api_key, password, account=account, connect=True, auto_renew=True)
    db = client['machine_data']
    result = 1;
    
   # Pull last entry from Cloudant
    sample_query = cloudant.query.Query(db, selector={'time': {'$gt': 0}})
    for doc in sample_query(limit=1)['docs']:
        SQL = "INSERT INTO PAPER_DATA.SENSOR_DATA (TIME, SENSOR_ID, VALUE) VALUES (?, ?, ?);"
        stmt = ibm_db.prepare(dbu, SQL)
        ibm_db.bind_param(stmt, 1, doc["time"])
        ibm_db.bind_param(stmt, 2, doc["id"])
        
        if doc["id"] == "ductTemp":
            ibm_db.bind_param(stmt, 3, doc["temp"])
        elif doc["id"] == "ductHumidity":
            ibm_db.bind_param(stmt, 3, doc["humidity"])
        elif doc["id"] == "simTemp":
            ibm_db.bind_param(stmt, 3, doc["temp"])
        elif doc["id"] == "ambientHumidity":
            ibm_db.bind_param(stmt, 3, doc["humidity"])
        elif doc["id"] == "ambientTemp":
            ibm_db.bind_param(stmt, 3, doc["temp"])
        
        
        ibm_db.execute(stmt)
    
    client.disconnect()
    
    return result
    
    