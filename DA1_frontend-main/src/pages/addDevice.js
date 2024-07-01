import React from 'react'
import { useState, useContext } from 'react'
import { myFetch } from '../App';
import style from '../styles/addDevice.module.css'
import TextField from '@mui/material/TextField';
import Select from '@mui/material/Select';
import MenuItem from '@mui/material/MenuItem';
import { Button, InputLabel } from '@mui/material';
import FormControl from '@mui/material/FormControl';
import { HomeContext } from './home';
import { useNavigate } from 'react-router-dom'; 
import Stack from '@mui/material/Stack';

export const AddDevice = () => {
    const [id, setId] = useState(() => "")
    const [name, setName] = useState(() => "")
    const [type, setType] = useState(() => "")
    const [message, setMessage] = useState(() => "")
    const navigate = useNavigate()
    const setDevices = useContext(HomeContext)

    const submitHandler = (event) => {
        event.preventDefault()
        console.log({id, name, type})
        myFetch(`/api/user/device/${type}/add`, {
            body : { id, name }
        })
        .then(res => {
            setMessage(res.message)
            console.log(res)
            if(res.success) {
                setDevices((pre) => [{...res.device, type}, ...pre])
            }
        })
    }

    return (
    <div >
        <form onSubmit={submitHandler} className={style.add_device_container}>
            <FormControl variant="standard" sx={{margin : 1.5 }}>
                <InputLabel required >Type</InputLabel>
                <Select
                    padding={0}
                    width={1}
                    required
                    value={type}
                    onChange={(event) => setType(event.target.value)}
                    label="Type"
                >
                    <MenuItem value={"fan"}>Fan</MenuItem>
                    <MenuItem value={"led"}>Led</MenuItem>
                    <MenuItem value={"door"}>Door</MenuItem>
                </Select>
            </FormControl>
            <TextField
                required
                label="id"
                value={id}
                onChange={(event) => setId(event.target.value)}
                sx={{margin : 1.5}}
            />
            <TextField
                required
                label="name"
                value={name}
                onChange={(event) => setName(event.target.value)}
                sx={{margin : 1.5}}
            />
            {message ? <p>{message}</p> : ""}
            <Stack 
                spacing={2} 
                direction="row"
                justifyContent="space-between"
                alignItems="center"
                padding={1}
            >
                <Button variant="contained" type='submit' sx={{width: 1, minWidth: 100}} >Add</Button>            
                <Button variant="contained" type='button' onClick={() => navigate('/')} sx={{width: 1, minWidth: 100}} >Return</Button>            
            </Stack>
        </form>
    </div>
    )
}