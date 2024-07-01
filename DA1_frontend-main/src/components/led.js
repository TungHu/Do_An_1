import { useState, useEffect, useContext } from 'react';
import { myFetch } from "../App";
import dayjs from 'dayjs';
import { LocalizationProvider } from '@mui/x-date-pickers/LocalizationProvider';
import { AdapterDayjs } from '@mui/x-date-pickers/AdapterDayjs';
import { MobileTimePicker } from '@mui/x-date-pickers/MobileTimePicker';
import { DeviceContext } from "./device"
import { InputLabel } from '@mui/material';
import Select from '@mui/material/Select';
import MenuItem from '@mui/material/MenuItem';
import FormControl from '@mui/material/FormControl';
import Stack from '@mui/material/Stack';
import Switch from "./switch";

export default function Led() {
    const {device} = useContext(DeviceContext)
    const [time, setTime] = useState(() => dayjs(device.schedule.time))
    const [option, setOption] = useState(() => device.schedule.option)

    useEffect(() => {
        const schedule = {option, time : time.toDate()}
        console.log(schedule)
        myFetch("/api/user/device/led/schedule", {
            body : {
                deviceId : device._id,
                schedule
            }
        })
        .then(res => console.log(res))

    }, [time, option])

    return (
        <div>
            <Switch></Switch>
            <Stack direction="row" spacing={2}>
                <FormControl variant="standard" sx={{margin : 1.5, width : 100 }}>
                    <InputLabel></InputLabel>
                    <Select
                        padding={0}
                        required
                        value={option}
                        onChange={(event) => setOption(event.target.value)}
                    >
                        <MenuItem value={"NONE"}>NONE</MenuItem>
                        <MenuItem value={"OFF"}>OFF</MenuItem>
                        <MenuItem value={"ON"}>ON</MenuItem>
                    </Select>
                </FormControl>
                <LocalizationProvider dateAdapter={AdapterDayjs}>
                    <MobileTimePicker
                        label="Time"
                        ampm={false}
                        value={time}
                        onChange={(newValue) => setTime(newValue)}
                    />
                </LocalizationProvider>
            </Stack>
        </div>
    );
}