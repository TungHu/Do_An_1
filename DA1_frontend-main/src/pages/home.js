import React, { useState, useEffect, useContext } from 'react'
import Device from "../components/device"
import { useNavigate } from 'react-router-dom'; 
import mainStyle from '../styles/home.module.css'
import deviceStype from '../styles/device.module.css'
import Button from '@mui/material/Button';
import { Outlet } from "react-router-dom";
import { createContext  } from "react";
import Stack from '@mui/material/Stack';
import { myFetch, AppContext } from '../App';

export const HomeContext = createContext(null);

function Home() {
    const navigate = useNavigate();
    const [devices, setDevices] = useState([]);
    const { socket } = useContext(AppContext);

    const logoutHandler = () => {
        myFetch('/api/user/auth/logout')
        .then(res => {
            if(res.success)
                navigate('/login')
            console.log(res)
        })
    }

    useEffect(() => {
        socket.connect();
        console.log("connect to socket server");
        myFetch('/api/user/device')
        .then(res => setDevices(res));
    }, []);

    return (
        <div>
            <HomeContext.Provider value={setDevices} >
                <div className={mainStyle.body_container}>
                    <Stack
                        spacing={10} 
                        direction="row"
                        justifyContent="space-between"
                        alignItems="center"
                    >
                        <Button sx={{width : 125}} variant="contained" onClick={() => navigate('/add')}>Add device</Button>
                        <Button sx={{width : 125}} variant="contained" onClick={logoutHandler}>Logout</Button>
                    </Stack>
                    <div className={deviceStype.device_container}>
                        {devices.map(device => <Device key={device._id} device={device} />)}
                    </div>
                    <Outlet/>
                </div>
            </HomeContext.Provider>
        </div>
    );
}

export default Home