package com.example.esp8266controller;

import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;
import java.util.concurrent.atomic.AtomicReference;

@RestController
@CrossOrigin(origins = "*")
public class EspController {

    // ✅ Set a temporary default IP (overwritten on ESP registration)
    private final AtomicReference<String> nodeIp = new AtomicReference<>("http://192.168.0.0");
    private final RestTemplate restTemplate = new RestTemplate();

    // ✅ Called by ESP8266 during setup to register its IP
    @GetMapping("/register-ip")
    public String registerIp(@RequestParam String ip) {
        String fullIp = "http://" + ip;
        nodeIp.set(fullIp);
        System.out.println("ESP8266 IP Registered: " + fullIp);
        return "IP Registered: " + fullIp;
    }

    // ✅ Called from frontend to send ON/OFF to ESP
    @PostMapping("/bulb/{bulbId}/{action}")
    public String controlBulb(@PathVariable int bulbId, @PathVariable String action) {
        String espBaseUrl = nodeIp.get();

        // ✅ Validate and sanitize action
        if (!action.equalsIgnoreCase("on") && !action.equalsIgnoreCase("off")) {
            return "Invalid action. Use 'on' or 'off'";
        }

        // ✅ Construct full URL for ESP endpoint
        String url = espBaseUrl + "/bulb" + bulbId + "/" + action;

        try {
            String response = restTemplate.getForObject(url, String.class);
            System.out.println("Command sent to ESP: " + url + " → Response: " + response);
            return response;
        } catch (Exception e) {
            System.err.println("Failed to send command to ESP: " + e.getMessage());
            return "Error: Failed to connect to ESP. Check IP and Wi-Fi.";
        }
    }
}
