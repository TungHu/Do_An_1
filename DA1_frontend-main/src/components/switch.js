import { useState, useContext, useEffect } from "react";
import SyncLoader from "react-spinners/SyncLoader";
import { DeviceContext } from "./device";
import { AppContext, myFetch } from "../App";
import LiSwitch from '@mui/material/Switch';
import style from '../styles/device.module.css'

function Switch() {
    const {socket} = useContext(AppContext)
    const {device, setIsConnected} = useContext(DeviceContext)
    const [state, setState] = useState(() => device.state);
    const [loading, setLoading] = useState(() => false);

    const onOffHandler = (event) => {
        const {checked} = event.target
        setState(checked);
        setLoading(true);
        myFetch(`/api/user/device/${device.type}/state`, {
            body : { 
                state : Number(checked),
                deviceId : device._id,
            }
        })
        .then(res => {
            console.log(res);
            if(res.success)
                setLoading(false)
            else
                setIsConnected(false)
        })
    };

    useEffect(() => {
        socket.on(`sync/${device._id}/state`, ({newState}) => {
            const time = new Date();
            console.log("on sync, time", `${time.toLocaleTimeString()}.${time.getMilliseconds()}`);
            setState(newState);
        })
        return () => {
            socket.off(`sync/${device._id}/state`)
        }      
    }, [])

    return (
        <div className={style.switch_containter}>
            <label>
                { device.type === "door" ? (state ? "OPEN" : "CLOSE") : (state ? "ON" : "OFF")}    
                <LiSwitch 
                    checked={!!state}
                    onChange={onOffHandler}
                />
            </label>
            <div className={style.switch_loading}>
                <SyncLoader loading={loading} size={7} color="#36d7b7"/>
            </div>
        </div>
    );
}

export default Switch;