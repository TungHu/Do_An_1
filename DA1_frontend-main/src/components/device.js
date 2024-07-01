import { useState, createContext } from "react";
import style from '../styles/device.module.css'
import Fan from "./fan"
import Led from "./led"
import Door from "./door"

export const DeviceContext = createContext(null)

export default function Device({ device }) {
    const [isConnected, setIsConnected] = useState(() => true)
    const {type} = device

    return (
            <div className= {`${style.device} ${isConnected ? style.device_conected : style.device_disconected}`}>
                <DeviceContext.Provider value={{setIsConnected, device}} >
                    <p className={style.connectStatus}> {isConnected ? "connected" : "disconnected"} </p>
                    <p> {device.name}</p>
                    {isConnected ? <div>
                        {type == "fan" ? <Fan/> :
                        type == "led" ? <Led/> :
                        type == "door" ? <Door/> : <div/>}
                    </div> :
                    <div/>}
                </DeviceContext.Provider>
            </div>
    )
}